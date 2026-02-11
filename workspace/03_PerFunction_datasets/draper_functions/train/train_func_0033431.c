libfvalue_split_utf8_string_get_segment_by_index(
     libfvalue_split_utf8_string_t *split_string,
     int segment_index,
     uint8_t **utf8_string_segment,
     size_t *utf8_string_segment_size,
     libcerror_error_t **error )
{
	libfvalue_internal_split_utf8_string_t *internal_split_string = NULL;
	static char *function                                         = "libfvalue_split_utf8_string_get_segment_by_index";

	if( split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split string.",
		 function );

		return( -1 );
	}
	internal_split_string = (libfvalue_internal_split_utf8_string_t *) split_string;

	if( ( segment_index < 0 )
	 || ( segment_index >= internal_split_string->number_of_segments ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment index value out of bounds.",
		 function );

		return( -1 );
	}
	if( utf8_string_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string segment.",
		 function );

		return( -1 );
	}
	if( utf8_string_segment_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string segment size.",
		 function );

		return( -1 );
	}
	*utf8_string_segment      = internal_split_string->segments[ segment_index ];
	*utf8_string_segment_size = internal_split_string->segment_sizes[ segment_index ];

	return( 1 );
}
