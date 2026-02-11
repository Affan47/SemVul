xi_get_error_string( xi_err_t e )
{
#ifdef XI_OPT_NO_ERROR_STRINGS
    return ( const char* ) &e;
#else
    return xi_err_string[ XI_MIN( ( short ) e, XI_ERR_COUNT - 1 ) ];
#endif
}
