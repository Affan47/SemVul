libcdata_list_insert_value(
     libcdata_list_t *list,
     intptr_t *value,
     int (*value_compare_function)(
            intptr_t *first_value,
            intptr_t *second_value,
            libcerror_error_t **error ),
     uint8_t insert_flags,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element = NULL;
	static char *function                 = "libcdata_list_insert_value";
	int result                            = 0;

	if( libcdata_list_element_initialize(
	     &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create list element.",
		 function );

		return( -1 );
	}
	if( libcdata_list_element_set_value(
	     list_element,
	     value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to set value of list element.",
		 function );

		goto on_error;
	}
	result = libcdata_list_insert_element(
	          list,
	          list_element,
	          value_compare_function,
	          insert_flags,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to insert element to list.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		if( libcdata_list_element_free(
		     &list_element,
		     NULL,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free list element.",
			 function );

			goto on_error;
		}
	}
	return( result );

on_error:
	if( list_element != NULL )
	{
		libcdata_list_element_free(
		 &list_element,
		 NULL,
		 NULL );
	}
	return( -1 );
}
