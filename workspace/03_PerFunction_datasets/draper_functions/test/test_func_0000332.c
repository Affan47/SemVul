local_from_stream( std::ifstream & stream, const byteorder & bo )
    {
        UInt8 c, flag;
        for ( ; ; )
        {
            c = stream.get();
            if(!stream.good() || c == ';')
                return false;
            if(c == '!')
            {
                void_vector<UInt8> extensions;


                read_field( stream, bo, c );
                while (read_data_block(stream, extensions) > 0) ;
            }
            if(c == ',')
                break;
        }

        UInt16 x,y;

        read_field( stream, bo, x );
        read_field( stream, bo, y );
        read_field( stream, bo, width );
        read_field( stream, bo, height );
        read_field( stream, bo, flag );
        interlace=BitSet(flag,0x40);
        if(BitSet(flag,0x80))
        {
            global_colormap = false;
            bits_per_pixel = (flag & 0x07)+1;
            maplength = 3*( 1 << bits_per_pixel);
        }
        return true;
    }
