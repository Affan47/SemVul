libcfile_stream_seek_offset(
         libcfile_stream_t *stream,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libcfile_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libcfile_stream_seek_offset";
	int result                                  = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libcfile_internal_stream_t *) stream;

	if( internal_stream->stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && ( LONG_MAX < INT64_MAX )
	if( offset > (off64_t) LONG_MAX )
#else
	if( offset > (off64_t) INT64_MAX )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	result = fseek(
	          internal_stream->stream,
	          (long) offset,
	          whence );
#elif defined( HAVE_FSEEKO64 ) && !defined( HAVE_FSEEKO )
	result = fseeko64(
	          internal_stream->stream,
	          offset,
	          whence );
#else
	result = fseeko(
	          internal_stream->stream,
	          (off_t) offset,
	          whence );
#endif
	if( result != 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 errno,
		 "%s: unable to seek offset in stream.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	offset = (off64_t) ftell(
	                    internal_stream->stream );
#elif defined( HAVE_FTELLO64 ) && !defined( HAVE_FTELLO )
	offset = ftello64(
	          internal_stream->stream );
#else
	offset = (off64_t) ftello(
	                    internal_stream->stream );
#endif
	if( offset < 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to get offset from stream.",
		 function );

		return( -1 );
	}
	return( offset );
}
