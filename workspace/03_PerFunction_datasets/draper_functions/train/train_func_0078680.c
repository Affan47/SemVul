libodraw_track_value_set(
     libodraw_track_value_t *track_value,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     uint8_t type,
     int data_file_index,
     uint64_t data_file_start_sector,
     libcerror_error_t **error )
{
	static char *function = "libodraw_track_value_set";

	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track value.",
		 function );

		return( -1 );
	}
	if( start_sector > (uint64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid start sector value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( number_of_sectors > (uint64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of sectors value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( type != LIBODRAW_TRACK_TYPE_UNKNOWN )
	 && ( type != LIBODRAW_TRACK_TYPE_AUDIO )
	 && ( type != LIBODRAW_TRACK_TYPE_CDG )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE1_2048 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE1_2352 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE2_2048 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE2_2324 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE2_2336 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE2_2352 )
	 && ( type != LIBODRAW_TRACK_TYPE_CDI_2336 )
	 && ( type != LIBODRAW_TRACK_TYPE_CDI_2352 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported type.",
		 function );

		return( -1 );
	}
	if( data_file_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid data file index value less than zero.",
		 function );

		return( -1 );
	}
	if( data_file_start_sector > (uint64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data file start sector value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_file_start_sector > start_sector )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: data file start sector value out of bounds.",
		 function );

		return( -1 );
	}
	switch( type )
	{
		case LIBODRAW_TRACK_TYPE_MODE1_2048:
		case LIBODRAW_TRACK_TYPE_MODE2_2048:
			track_value->bytes_per_sector = 2048;

			break;

		case LIBODRAW_TRACK_TYPE_MODE2_2324:
			track_value->bytes_per_sector = 2324;

			break;

		case LIBODRAW_TRACK_TYPE_MODE2_2336:
		case LIBODRAW_TRACK_TYPE_CDI_2336:
			track_value->bytes_per_sector = 2336;

			break;

		case LIBODRAW_TRACK_TYPE_AUDIO:
		case LIBODRAW_TRACK_TYPE_MODE1_2352:
		case LIBODRAW_TRACK_TYPE_MODE2_2352:
		case LIBODRAW_TRACK_TYPE_CDI_2352:
			track_value->bytes_per_sector = 2352;

			break;

		case LIBODRAW_TRACK_TYPE_CDG:
			track_value->bytes_per_sector = 2448;

			break;
	}
	track_value->start_sector           = start_sector;
	track_value->end_sector             = start_sector + number_of_sectors;
	track_value->number_of_sectors      = number_of_sectors;
	track_value->type                   = type;
	track_value->data_file_index        = data_file_index;
	track_value->data_file_start_sector = data_file_start_sector;
	track_value->data_file_offset       = data_file_start_sector * track_value->bytes_per_sector;

	return( 1 );
}
