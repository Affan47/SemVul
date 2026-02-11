libsmraw_information_file_set_name(
     libsmraw_information_file_t *information_file,
     const libcstring_system_character_t *name,
     size_t name_length,
     libcerror_error_t **error )
{
	static char *function = "libsmraw_information_file_set_name";

	if( information_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid information file.",
		 function );

		return( -1 );
	}
	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( name_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	information_file->name = libcstring_system_string_allocate(
	                          name_length + 1 );

	if( information_file->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to allocate name.",
		 function );

		return( -1 );
	}
	if( libcstring_system_string_copy(
	     information_file->name,
	     name,
	     name_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
	information_file->name[ name_length ] = 0;

	information_file->name_size = name_length + 1;

	return( 1 );
}
