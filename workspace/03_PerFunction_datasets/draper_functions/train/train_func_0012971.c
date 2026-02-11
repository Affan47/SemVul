storage_media_buffer_free(
     storage_media_buffer_t **buffer,
     libcerror_error_t **error )
{
	static char *function = "storage_media_buffer_free";

	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( *buffer != NULL )
	{
		if( ( *buffer )->raw_buffer != NULL )
		{
			memory_free(
			 ( *buffer )->raw_buffer );
		}
#if defined( HAVE_LOW_LEVEL_FUNCTIONS )
		if( ( *buffer )->compression_buffer != NULL )
		{
			memory_free(
			 ( *buffer )->compression_buffer );
		}
#endif
		memory_free(
		 *buffer );

		*buffer = NULL;
	}
	return( 1 );
}
