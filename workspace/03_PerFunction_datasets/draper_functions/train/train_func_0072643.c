libfcache_cache_value_initialize(
     libfcache_cache_value_t **cache_value,
     libcerror_error_t **error )
{
	libfcache_internal_cache_value_t *internal_cache_value = NULL;
	static char *function                                  = "libfcache_cache_value_initialize";

	if( cache_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache value.",
		 function );

		return( -1 );
	}
	if( *cache_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid cache value value already set.",
		 function );

		return( -1 );
	}
	internal_cache_value = memory_allocate_structure(
	                        libfcache_internal_cache_value_t );

	if( internal_cache_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create cache value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_cache_value,
	     0,
	     sizeof( libfcache_internal_cache_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear cache value.",
		 function );

		goto on_error;
	}
	internal_cache_value->file_index = -1;
	internal_cache_value->offset     = (off64_t) -1;

	*cache_value = (libfcache_cache_value_t *) internal_cache_value;

	return( 1 );

on_error:
	if( internal_cache_value != NULL )
	{
		memory_free(
		 internal_cache_value );
	}
	return( -1 );
}
