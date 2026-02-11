libfvalue_table_free(
     libfvalue_table_t **table,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_table_free";
	int result            = 1;

	if( table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid table.",
		 function );

		return( -1 );
	}
	if( *table != NULL )
	{
		if( libfvalue_table_free_as_value(
		     (intptr_t *) *table,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free table.",
			 function );

			result = -1;
		}
		*table = NULL;
	}
	return( result );
}
