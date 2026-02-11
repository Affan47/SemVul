libfvalue_binary_data_copy_from_byte_stream(
     libfvalue_binary_data_t *binary_data,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int encoding,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_binary_data_copy_from_byte_stream";

	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( encoding != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported encoding.",
		 function );

		return( -1 );
	}
	binary_data->data      = byte_stream;
	binary_data->data_size = byte_stream_size;

	return( 1 );
}
