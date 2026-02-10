get_seed_file_info( char *file_name, seed_file_info* file_info,
                         bool print_file_info ) {
    FILE *file_handle = NULL;
    uint8_t *buffer = NULL;
    long end_offset;
    long file_length;
    long records_read;
    seed_header header_seed;
    uint8_t* header_ptr = NULL;

    file_info->good = false;

    if ( print_file_info ) {
        printf( "Getting file info for %s\n", file_name );
    }

    if ( !file_name ) {
        fprintf( stderr, "No file name supplied.\n" );
        goto clean;
    }

    buffer = malloc( (size_t)(RECORD_SIZE) );
    if ( !buffer ) {
        fprintf( stderr, "Could not allocate memory for read buffer.\n" );
        goto clean;
    }

    file_handle = fopen( file_name, "rb" );
    if ( !file_handle ) {
        fprintf( stderr, "Unable to open file '%s' for reading.\n", file_name );
        goto clean;
    }

    fseek( file_handle, 0, SEEK_END );
    file_length = ftell( file_handle );
    if ( file_length < (long)RECORD_SIZE ) {
        fprintf( stderr, "File is too small to contain seed records.\n" );
        goto clean;
    }
    end_offset = file_length % (long)RECORD_SIZE
                    ? file_length / (long)RECORD_SIZE
                        ? file_length - (file_length % (long)RECORD_SIZE) - (long)RECORD_SIZE
                        : (long)0
                    : file_length - (long)RECORD_SIZE;
    if ( print_file_info ) {
        printf( "File size is %li bytes.\n", file_length );
    }

    if ( print_file_info ) {
        printf( "Reading at position [%li]\n", (long)0 );
    }
    fseek( file_handle, 0, SEEK_SET );
    records_read = fread( buffer, (size_t)RECORD_SIZE, 1, file_handle );
    header_ptr = buffer;
    loadseedhdr( (pbyte *)&header_ptr, &header_seed, false );
    if ( print_file_info ) {
        print_seed_header( &header_seed );
    }
    if ( !records_read ) {
        goto clean;
    }
    file_info->start_time = header_seed.starting_time;

    if ( print_file_info ) {
        printf( "Reading at position [%li]\n", end_offset );
    }
    fseek( file_handle, end_offset, SEEK_SET );
    records_read = fread( buffer, (size_t)RECORD_SIZE, 1, file_handle );
    header_ptr = buffer;
    loadseedhdr( (pbyte *)&header_ptr, &header_seed, false );
    if ( print_file_info ) {
        print_seed_header( &header_seed );
    }
    if ( !records_read ) {
        goto clean;
    }
    file_info->end_time = header_seed.starting_time;

    fclose( file_handle );

    file_info->length = file_length;
    file_info->good = true;
clean:
    if ( buffer ) {
        free( buffer );
    }
}
