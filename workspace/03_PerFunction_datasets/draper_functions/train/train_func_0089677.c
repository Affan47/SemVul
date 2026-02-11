libcdata_array_empty(
     libcdata_array_t *array,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     libcerror_error_t **error )
{
	libcdata_internal_array_t *internal_array = NULL;
	static char *function                     = "libcdata_array_empty";

	if( array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid array.",
		 function );

		return( -1 );
	}
	internal_array = (libcdata_internal_array_t *) array;

	if( libcdata_array_clear(
	     array,
	     entry_free_function,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear array.",
		 function );

		return( -1 );
	}
	internal_array->number_of_entries = 0;

	return( 1 );
}
