process_script ( struct image *image,
			    int ( * process_line ) ( const char *line ),
			    int ( * terminate ) ( int rc ) ) {
	off_t eol;
	size_t len;
	int rc;

	script_offset = 0;

	do {


		eol = memchr_user ( image->data, script_offset, '\n',
				    ( image->len - script_offset ) );
		if ( eol < 0 )
			eol = image->len;
		len = ( eol - script_offset );


		{
			char cmdbuf[ len + 1 ];

			copy_from_user ( cmdbuf, image->data,
					 script_offset, len );
			cmdbuf[len] = '\0';
			DBG ( "$ %s\n", cmdbuf );


			script_offset += ( len + 1 );


			rc = process_line ( cmdbuf );
			if ( terminate ( rc ) )
				return rc;
		}

	} while ( script_offset < image->len );

	return rc;
}
