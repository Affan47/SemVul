from_stream( std::ifstream & stream, byteorder & bo )
    {

        field_type scratch;


        stream.seekg( 2, std::ios::cur );


        vigra_precondition( stream.get() == XV_IMAGE_REL_NUM,
                            "file format release unsupported" );


        vigra_precondition( stream.get() == XV_IMAGE_VER_NUM,
                            "file format version unsupported" );


        const char machine_dep = stream.get();
        if ( machine_dep == VFF_DEP_BIGENDIAN )
            bo.set("big endian");
        else if ( machine_dep == VFF_DEP_LITENDIAN )
            bo.set("little endian");
        else vigra_fail( "endianness unsupported" );


        stream.seekg( 0x208, std::ios::beg );


        read_field( stream, bo, row_size );


        read_field( stream, bo, col_size );


        stream.seekg( 20, std::ios::cur );

        read_field( stream, bo, scratch );
        vigra_precondition( scratch != VFF_LOC_EXPLICIT,
                            "explicit locations are unsupported" );


        stream.seekg( 4, std::ios::cur );


        read_field( stream, bo, scratch );
        vigra_precondition( scratch < 2,
                            "multiple images are unsupported" );

        read_field( stream, bo, num_data_bands );

        read_field( stream, bo, data_storage_type );
        vigra_precondition( data_storage_type != VFF_TYP_BIT,
                            "bit storage type unsupported" );
        vigra_precondition( data_storage_type != VFF_TYP_COMPLEX,
                            "complex storage type unsupported" );
        vigra_precondition( data_storage_type != VFF_TYP_DCOMPLEX,
                            "double complex storage type unsupported" );

        read_field( stream, bo, data_encode_scheme );
        vigra_precondition( data_encode_scheme == VFF_DES_RAW,
                            "data compression unsupported" );

        read_field( stream, bo, map_scheme );
        vigra_precondition( map_scheme != VFF_MS_CYCLE,
                            "map cycling unsupported" );


        if ( map_scheme != VFF_MS_NONE ) {

            read_field( stream, bo, map_storage_type );
            vigra_precondition( map_storage_type != VFF_MAPTYP_COMPLEX,
                                "complex storage type unsupported" );
            vigra_precondition( map_storage_type != VFF_MAPTYP_NONE,
                                "invalid maptype" );

            read_field( stream, bo, map_row_size );
            read_field( stream, bo, map_col_size );
        }


        stream.seekg( 1024, std::ios::beg );
    }
