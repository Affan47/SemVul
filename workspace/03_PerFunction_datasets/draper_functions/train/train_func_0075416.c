_gcry_xrealloc( void *a, size_t n )
{
  void *p;

  while ( !(p = _gcry_realloc( a, n )) )
    {
      if ( fips_mode ()
           || !outofcore_handler
           || !outofcore_handler (outofcore_handler_value, n,
                                  _gcry_is_secure(a)? 3:2))
        {
          _gcry_fatal_error (gpg_err_code_from_errno (errno), NULL );
	}
    }
    return p;
}
