libcdata_array_prepend_entry(
     libcdata_array_t *array,
     intptr_t *entry,
     libcerror_error_t **error )
{
	libcdata_internal_array_t *internal_array = NULL;
	static char *function                     = "libcdata_array_prepend_entry";
	int entry_iterator                        = 0;

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

	if( libcdata_array_resize(
	     array,
	     internal_array->number_of_entries + 1,
	     NULL,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize array.",
		 function );

		return( -1 );
	}
	if( internal_array->entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid array - missing entries.",
		 function );

		return( -1 );
	}
	if( internal_array->number_of_entries > 1 )
	{
		for( entry_iterator = internal_array->number_of_entries - 2;
		     entry_iterator >= 0;
		     entry_iterator-- )
		{
			internal_array->entries[ entry_iterator + 1 ] = internal_array->entries[ entry_iterator ];
		}
	}
	internal_array->entries[ 0 ] = entry;

	return( 1 );
}
