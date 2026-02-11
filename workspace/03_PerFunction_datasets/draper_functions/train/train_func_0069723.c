libcdata_array_clone(
     libcdata_array_t **destination_array,
     libcdata_array_t *source_array,
     int (*entry_free_function)(
            intptr_t **entry,
            libcerror_error_t **error ),
     int (*entry_clone_function)(
            intptr_t **destination_entry,
            intptr_t *source_entry,
            libcerror_error_t **error ),
     libcerror_error_t **error )
{
	libcdata_internal_array_t *internal_destination_array = NULL;
	libcdata_internal_array_t *internal_source_array      = NULL;
	static char *function                                 = "libcdata_array_clone";
	int entry_iterator                                    = 0;

	if( destination_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination array.",
		 function );

		return( -1 );
	}
	if( *destination_array != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination array already set.",
		 function );

		return( -1 );
	}
	if( entry_free_function == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry free function.",
		 function );

		return( -1 );
	}
	if( entry_clone_function == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry clone function.",
		 function );

		return( -1 );
	}
	if( source_array == NULL )
	{
		*destination_array = NULL;

		return( 1 );
	}
	internal_source_array = (libcdata_internal_array_t *) source_array;

	if( libcdata_array_initialize(
	     destination_array,
	     internal_source_array->number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create destination array.",
		 function );

		goto on_error;
	}
	if( *destination_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing destination array.",
		 function );

		goto on_error;
	}
	internal_destination_array = (libcdata_internal_array_t *) destination_array;

	if( internal_source_array->entries != NULL )
	{
		for( entry_iterator = 0;
		     entry_iterator < internal_source_array->number_of_entries;
		     entry_iterator++ )
		{
			if( internal_source_array->entries[ entry_iterator ] != NULL )
			{
				if( entry_clone_function(
				     &( internal_destination_array->entries[ entry_iterator ] ),
				     internal_source_array->entries[ entry_iterator ],
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create destination array entry: %d.",
					 function,
					 entry_iterator );

					goto on_error;
				}
			}
		}
	}
	return( 1 );

on_error:
	if( *destination_array != NULL )
	{
		libcdata_array_free(
		 destination_array,
		 entry_free_function,
		 NULL );
	}
	return( -1 );
}
