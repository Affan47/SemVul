read_bands( std::ifstream & stream, byteorder & bo )
    {
        const unsigned int bands_size = width * height * components;

        if ( header.data_storage_type == VFF_TYP_1_BYTE ) {
            typedef void_vector<UInt8> bands_type;
            bands_type & castbands = static_cast< bands_type & >(bands);
            castbands.resize(bands_size);
            read_array( stream, bo, castbands.data(), bands_size );
            pixelType = "UINT8";
        } else if ( header.data_storage_type == VFF_TYP_2_BYTE ) {
            typedef void_vector<Int16> bands_type;
            bands_type & castbands = static_cast< bands_type & >(bands);
            castbands.resize(bands_size);
            read_array( stream, bo, castbands.data(), bands_size );
            pixelType = "INT16";
        } else if ( header.data_storage_type == VFF_TYP_4_BYTE ) {
            typedef void_vector<Int32> bands_type;
            bands_type & castbands = static_cast< bands_type & >(bands);
            castbands.resize(bands_size);
            read_array( stream, bo, castbands.data(), bands_size );
            pixelType = "INT32";
        } else if ( header.data_storage_type == VFF_TYP_FLOAT ) {
            typedef void_vector<float> bands_type;
            bands_type & castbands = static_cast< bands_type & >(bands);
            castbands.resize(bands_size);
            read_array( stream, bo, castbands.data(), bands_size );
            pixelType = "FLOAT";
        } else if ( header.data_storage_type == VFF_TYP_DOUBLE ) {
            typedef void_vector<double> bands_type;
            bands_type & castbands = static_cast< bands_type & >(bands);
            castbands.resize(bands_size);
            read_array( stream, bo, castbands.data(), bands_size );
            pixelType = "DOUBLE";
        } else
            vigra_precondition( false, "storage type unsupported" );
    }
