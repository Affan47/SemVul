fli_get_syserror_msg( void )
{
    const char  *pp;

#ifdef HAVE_STRERROR
    pp = errno ? strerror( errno ) : "";
#else
    pp = errno ? sys_errlist[ errno ] : "";
#endif

    return pp;
}
