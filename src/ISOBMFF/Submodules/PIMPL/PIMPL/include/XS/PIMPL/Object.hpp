/*******************************************************************************
 * Copyright (c) 2015, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/*!
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @brief       Declaration of the XS::PIMPL::Object template class
 */

#ifndef XS_PIMPL_OBJECT_H
#define XS_PIMPL_OBJECT_H

#ifdef _WIN32
    #ifdef XS_PIMPL_EXPORTS
        #define XS_PIMPL_API    __declspec( dllexport )
    #else
        #define XS_PIMPL_API    __declspec( dllimport )
    #endif
#else
    #define     XS_PIMPL_API    
#endif

namespace XS
{
    namespace PIMPL
    {
        /*!
         * @brief           Generic PIMPL class
         * @tparam          T   The class extending XS::PIMPL::Object
         */
        template< class T >
        class XS_PIMPL_API Object
        {
            public:
                
                /* C++11 support is buggy on MSVC V120 toolset (see C4520)... */
                #if !defined( _MSC_FULL_VER ) || _MSC_FULL_VER >= 190024215
                
                /*!
                 * @brief       Class constructor (without parameters)
                 */ 
                Object( void );
                
                /*!
                 * @brief       Class constructor (with optional parameters)
                 */
                template< typename ... A > 
                Object( A & ... a );
                
                /*!
                 * @brief       Class constructor (with optional const parameters)
                 */
                template< typename ... A > 
                Object( const A & ... a );
                
                #else
                
                /*!
                 * @brief       Class constructor (no parameters)
                 */
                Object( void );
                
                /*!
                 * @brief       Class constructor (with parameters)
                 */
                template< typename A1, typename ... A2 > 
                Object( A1 a1, A2 ... a2 );
                
                #endif
                
                /*!
                 * @brief       Class copy constructor
                 * @param       o   Another object to be used as data source for the initialization
                 */
                Object( const Object< T > & o );
                
                /*!
                 * @brief       Class move constructor
                 * @param       o   Another object to be used as data source for the initialization
                 */
                Object( Object< T > && o );
                
                /*!
                 * @brief       Class destructor
                 */
                virtual ~Object( void );
                
                /*!
                 * @brief       Assignment operator
                 * @param       o   Another object to use as data source
                 */
                Object< T > & operator =( Object< T > o );
                
                /*!
                 * @brief           ADL - Swap function for XS::PIMPL::Object
                 * @param           o1  The first object to swap
                 * @param           o2  The second object to swap
                 */
                template< class U >
                friend void swap( Object< U > & o1, Object< U > & o2 );
                
            private:
                
                friend T;
                class  IMPL;
                
                /*!
                 * @brief       A pointer to the class' private implementation
                 */
                 IMPL * impl;
        };
    }
}

#endif /* XS_PIMPL_OBJECT_H */