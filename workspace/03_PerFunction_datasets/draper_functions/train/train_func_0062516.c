libcfile_file_is_open(
     libcfile_file_t *file,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_is_open";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libcfile_internal_file_t *) file;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( internal_file->handle == INVALID_HANDLE_VALUE )
#else
	if( internal_file->descriptor == -1 )
#endif
	{
		return( 0 );
	}
	return( 1 );
}
