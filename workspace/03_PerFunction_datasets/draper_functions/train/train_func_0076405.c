libbfio_pool_open_handle(
     libbfio_internal_pool_t *internal_pool,
     libbfio_handle_t *handle,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libbfio_pool_open_handle";
	int is_open                                = 0;

	if( internal_pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	if( internal_pool->last_used_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing last used list.",
		 function );

		return( -1 );
	}
	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	is_open = libbfio_handle_is_open(
	           handle,
	           error );

	if( is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if handle is open.",
		 function );

		return( -1 );
	}
	else if( is_open == 1 )
	{
		return( 1 );
	}
	if( internal_pool->maximum_number_of_open_handles != LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES )
	{
		if( libbfio_pool_append_handle_to_last_used_list(
		     internal_pool,
		     handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append handle to last used list.",
			 function );

			return( -1 );
		}
	}
	if( libbfio_handle_open(
	     handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libbfio_internal_handle_t *) handle;

	if( libbfio_handle_seek_offset(
	     handle,
	     internal_handle->offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	return( 1 );
}
