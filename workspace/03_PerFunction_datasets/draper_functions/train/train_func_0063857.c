libsmdev_ata_get_device_configuration(
     libcfile_file_t *device_file,
     struct hd_driveid *device_configuration,
     libcerror_error_t **error )
{
	static char *function = "libsmdev_ata_get_device_configuration";
	int read_count        = 0;

	if( device_configuration == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid device configuration.",
		 function );

		return( -1 );
	}
#if defined( HDIO_GET_IDENTITY )
	read_count = libcfile_file_io_control_read(
	              device_file,
	              HDIO_GET_IDENTITY,
	              NULL,
	              0,
	              (uint8_t *) device_configuration,
	              sizeof( struct hd_driveid ),
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_IOCTL_FAILED,
		 "%s: unable to query device file for: HDIO_GET_IDENTITY.",
		 function );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
		}
#endif
		libcerror_error_free(
		 error );

		return( 0 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: HDIO_GET_IDENTITY:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) device_configuration,
		 sizeof( struct hd_driveid ),
		 0 );

		libcnotify_printf(
		 "Feature sets:\n" );

		libcnotify_printf(
		 "SMART:\t\t\t%d\n",
		 ( device_configuration->command_set_1 & 0x0001 ) );

		libcnotify_printf(
		 "Security Mode:\t\t%d (%d)\n",
		 ( device_configuration->command_set_1 & 0x0002 ) >> 1,
		 ( device_configuration->dlf & 0x0001 ) );

		libcnotify_printf(
		 "Security Mode enabled:\t%d\n",
		 ( device_configuration->dlf & 0x0002 ) >> 1 );

		libcnotify_printf(
		 "Removable Media:\t%d\n",
		 ( device_configuration->command_set_1 & 0x0004 ) >> 2 );

		libcnotify_printf(
		 "HPA:\t\t\t%d\n",
		 ( device_configuration->command_set_1 & 0x0400 ) >> 10 );

		libcnotify_printf(
		 "DCO:\t\t\t%d\n",
		 ( device_configuration->command_set_2 & 0x0800 ) >> 11 );

		libcnotify_printf(
		 "Media serial:\t\t%d\n",
		 ( device_configuration->cfsse & 0x0004 ) >> 2 );

		libcnotify_printf(
		 "\n" );
	}
#endif
#endif
	return( 1 );
}
