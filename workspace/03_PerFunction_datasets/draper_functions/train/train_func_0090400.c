libcerror_error_backtrace_fprint(
     libcerror_error_t *error,
     FILE *stream )
{
	libcerror_internal_error_t *internal_error = NULL;
	int message_index                          = 0;
	int print_count                            = 0;
	int total_print_count                      = 0;

	if( error == NULL )
	{
		return( -1 );
	}
	internal_error = (libcerror_internal_error_t *) error;

	if( internal_error->messages == NULL )
	{
		return( -1 );
	}
	if( stream == NULL )
	{
		return( -1 );
	}
	for( message_index = 0;
	     message_index < internal_error->number_of_messages;
	     message_index++ )
	{
		if( internal_error->messages[ message_index ] != NULL )
		{
			print_count = fprintf(
			               stream,
			               "%" PRIs_LIBCSTRING_SYSTEM "\n",
			               internal_error->messages[ message_index ] );

			if( print_count <= -1 )
			{
				return( -1 );
			}
			total_print_count += print_count;
		}
	}
	return( total_print_count );
}
