libbfio_memory_range_open(
     libbfio_memory_range_io_handle_t *memory_range_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	static char *function = "libbfio_memory_range_open";

	if( memory_range_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid memory range IO handle.",
		 function );

		return( -1 );
	}
	if( memory_range_io_handle->range_start == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid memory range IO handle - missing range start.",
		 function );

		return( -1 );
	}
	if( memory_range_io_handle->is_open != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid memory range IO handle - already open.",
		 function );

		return( -1 );
	}


	if( ( ( access_flags & LIBBFIO_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBBFIO_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags: 0x%02x.",
		 function );

		return( -1 );
	}
	memory_range_io_handle->range_offset = 0;
	memory_range_io_handle->access_flags = access_flags;
	memory_range_io_handle->is_open      = 1;

	return( 1 );
}
