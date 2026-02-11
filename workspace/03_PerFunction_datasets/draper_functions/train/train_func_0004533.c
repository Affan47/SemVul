libsmdev_handle_get_track(
     libsmdev_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     uint8_t *type,
     libcerror_error_t **error )
{
	libsmdev_internal_handle_t *internal_handle = NULL;
	libsmdev_track_value_t *track_value         = NULL;
	static char *function                       = "libsmdev_handle_get_track";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libsmdev_internal_handle_t *) handle;

	if( libcdata_array_get_entry_by_index(
	     internal_handle->tracks_array,
	     index,
	     (intptr_t **) &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value: %d from array.",
		 function,
		 index );

		return( -1 );
	}
	if( libsmdev_track_value_get(
	     track_value,
	     start_sector,
	     number_of_sectors,
	     type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value.",
		 function );

		return( -1 );
	}
	return( 1 );
}
