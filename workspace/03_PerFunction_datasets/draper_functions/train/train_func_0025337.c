libuna_utf16_stream_copy_from_utf16(
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                    = "libuna_utf16_stream_copy_from_utf16";
	size_t utf16_stream_index                = 0;
	size_t utf16_string_index                = 0;
	libuna_utf16_character_t utf16_character = 0;

	if( utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_stream_copy_byte_order_mark(
	     utf16_stream,
	     utf16_stream_size,
	     &utf16_stream_index,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
		 "%s: unable to copy UTF-16 byte order mark.",
		 function );

		return( -1 );
	}


	while( utf16_string_index < utf16_string_size )
	{
		if( ( utf16_stream_index + 2 ) >= utf16_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 stream too small.",
			 function );

			return( -1 );
		}
		utf16_character = utf16_string[ utf16_string_index++ ];

		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_stream[ utf16_stream_index + 1 ] = (uint8_t) ( utf16_character & 0xff );
			utf16_character                      >>= 8;
			utf16_stream[ utf16_stream_index     ] = (uint8_t) ( utf16_character & 0xff );
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_stream[ utf16_stream_index     ] = (uint8_t) ( utf16_character & 0xff );
			utf16_character                      >>= 8;
			utf16_stream[ utf16_stream_index + 1 ] = (uint8_t) ( utf16_character & 0xff );
		}
		utf16_stream_index += 2;
	}
	return( 1 );
}
