main ( int argc, char **argv ) {
	struct input_file input;
	struct output_file output;
	struct zinfo_file zinfo;
	unsigned int i;

	if ( argc != 3 ) {
		fprintf ( stderr, "Syntax: %s file.bin file.zinfo "
			  "> file.zbin\n", argv[0] );
		exit ( 1 );
	}

	if ( read_input_file ( argv[1], &input ) < 0 )
		exit ( 1 );
	if ( read_zinfo_file ( argv[2], &zinfo ) < 0 )
		exit ( 1 );
	if ( alloc_output_file ( ( input.len * 4 ), &output ) < 0 )
		exit ( 1 );

	for ( i = 0 ; i < zinfo.num_entries ; i++ ) {
		if ( process_zinfo ( &input, &output,
				     &zinfo.zinfo[i] ) < 0 )
			exit ( 1 );
	}

	if ( write_output_file ( &output ) < 0 )
		exit ( 1 );

	return 0;
}
