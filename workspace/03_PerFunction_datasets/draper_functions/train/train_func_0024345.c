inchi_fprintf( FILE* f, const char* lpszFormat, ... )
{
int ret=0, ret2=0;
va_list argList;
    if (f)
    {
        my_va_start( argList, lpszFormat );
        ret = inchi_vfprintf( f, lpszFormat, argList );
        va_end( argList );

#if ( !defined(TARGET_API_LIB) && !defined(TARGET_LIB_FOR_WINCHI) )
        if ( f != stderr )
        {
            my_va_start( argList, lpszFormat );
            ret2 = vfprintf( stderr, lpszFormat, argList );
            va_end( argList );
        }
#endif
        return ret? ret : ret2;
    }
    return 0;
}
