fs_mkdir_p( char *path, mode_t mode )
{
	int err,pos,i;

	err = mkdir( path, mode );
	if( (err != NOERR) && errno == ENOENT ) {


		for( i = 0, pos = 0; path[ i ] != '\0'; i++ ) {
			if( path[ i ] == '/' )
				pos = i;
		}


		if( pos == 0 )
			return -1;

		path[ pos ] = '\0';
		err = fs_mkdir_p( path, mode );
		if( err != NOERR )
			return err;

		path[ pos ] = '/';
		err = mkdir( path, mode );
	}

    return err;
}
