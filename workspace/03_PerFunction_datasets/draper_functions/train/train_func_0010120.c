libfvalue_value_copy_to_64bit(
     libfvalue_value_t *value,
     int value_entry_index,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	libfvalue_internal_value_t *internal_value = NULL;
	intptr_t *value_instance                   = NULL;
	static char *function                      = "libfvalue_value_copy_to_64bit";
	size_t integer_value_size                  = 0;
	uint64_t integer_value                     = 0;
	int result                                 = 0;

	if( value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	internal_value = (libfvalue_internal_value_t *) value;

	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing value 64-bit.",
		 function );

		return( -1 );
	}
	if( internal_value->copy_to_integer != NULL )
	{
		if( libfvalue_value_get_value_instance_by_index(
		     value,
		     value_entry_index,
		     &value_instance,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value instance: %d.",
			 function,
			 value_entry_index );

			return( -1 );
		}
		if( value_instance != NULL )
		{
			if( internal_value->copy_to_integer(
			     value_instance,
			     &integer_value,
			     &integer_value_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy instance to integer value.",
				 function );

				return( -1 );
			}
			*value_64bit = (uint64_t) integer_value;

			result = 1;
		}
	}
	return( result );
}
