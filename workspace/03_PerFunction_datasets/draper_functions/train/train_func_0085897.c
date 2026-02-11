libbfio_file_is_open(
     libbfio_file_io_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libbfio_file_is_open";
	int result            = 0;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	result = libcfile_file_is_open(
	          file_io_handle->file,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if file is open.",
		 function );

		return( -1 );
	}
	return( result );
}
