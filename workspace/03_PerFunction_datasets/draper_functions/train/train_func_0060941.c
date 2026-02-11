write_hall_of_fame()
{
	char full_path[MAX_PATH+1];
	int  rc;
	File file;

	if (!misc.path_cat(full_path, sys.dir_config, HALL_OF_FAME_FILE_NAME, MAX_PATH))
	{
		ERR("Path to the hall of fame too long.\n");
		return 0;
	}

	rc = file.file_create( full_path, 0, 1 );

	if( !rc )
		return 0;


	if( rc )
		rc = file.file_write( hall_fame_array, sizeof(HallFame) * HALL_FAME_NUM );


	if( rc )
		rc = file.file_write( last_file_name, MAX_PATH+1 );

	file.file_close();

	return rc;
}
