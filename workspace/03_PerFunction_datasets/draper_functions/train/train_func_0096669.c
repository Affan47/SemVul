libfvalue_integer_copy_from_byte_stream(
     libfvalue_integer_t *integer,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int encoding,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_integer_copy_from_byte_stream";

	if( integer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid integer.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( encoding != LIBFVALUE_ENDIAN_BIG )
	 && ( encoding != LIBFVALUE_ENDIAN_LITTLE )
	 && ( encoding != LIBFVALUE_ENDIAN_NATIVE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported encoding.",
		 function );

		return( -1 );
	}
	switch( byte_stream_size )
	{
		case 1:
			integer->value = (uint64_t) *( (uint8_t *) byte_stream );

			break;

		case 2:
			if( encoding == LIBFVALUE_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint16_big_endian(
				 byte_stream,
				 integer->value );
			}
			else if( encoding == LIBFVALUE_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint16_little_endian(
				 byte_stream,
				 integer->value );
			}
			else
			{
				integer->value = (uint64_t) *( (uint16_t *) byte_stream );
			}
			break;

		case 4:
			if( encoding == LIBFVALUE_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint32_big_endian(
				 byte_stream,
				 integer->value );
			}
			else if( encoding == LIBFVALUE_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint32_little_endian(
				 byte_stream,
				 integer->value );
			}
			else
			{
				integer->value = (uint64_t) *( (uint32_t *) byte_stream );
			}
			break;

		case 8:
			if( encoding == LIBFVALUE_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint64_big_endian(
				 byte_stream,
				 integer->value );
			}
			else if( encoding == LIBFVALUE_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint64_little_endian(
				 byte_stream,
				 integer->value );
			}
			else
			{
				integer->value = (uint64_t) *( (uint64_t *) byte_stream );
			}
			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported byte stream size: %" PRIzd ".",
			 function,
			 byte_stream_size );

			return( -1 );
	}
	integer->value_size = byte_stream_size * 8;

	return( 1 );
}
