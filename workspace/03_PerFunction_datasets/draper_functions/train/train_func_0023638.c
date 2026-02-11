plusd_disk_write( plusd_drive_number which, const char *filename )
{
  wd_fdc_drive *d = &plusd_drives[ which ];
  int error;

  d->disk.type = DISK_TYPE_NONE;
  if( filename == NULL ) filename = d->disk.filename;
  error = disk_write( &d->disk, filename );

  if( error != DISK_OK ) {
    ui_error( UI_ERROR_ERROR, "couldn't write '%s' file: %s", filename,
	      disk_strerror( error ) );
    return 1;
  }
  if( d->disk.filename && strcmp( filename, d->disk.filename ) ) {
    free( d->disk.filename );
    d->disk.filename = utils_safe_strdup( filename );
  }

  return 0;
}
