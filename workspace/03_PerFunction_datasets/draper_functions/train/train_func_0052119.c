write_raw()
    {
        if ( pixeltype == "UINT8" ) {


            typedef void_vector< UInt8 > vector_type;
            vector_type & cbands = static_cast< vector_type & >(bands);


            stream.write( reinterpret_cast< char * >(cbands.data()),
                          height * width * components );

        } else if ( pixeltype == "UINT16" ) {


            typedef void_vector<UInt16> vector_type;
            vector_type & cbands = static_cast< vector_type & >(bands);


            byteorder bo( "big endian" );

            write_array( stream, bo, cbands.data(),
                         height * width * components );
        } else {
          vigra_postcondition( false, "internal error" );
        }
    }
