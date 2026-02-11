bits_to_string(uint64_t text, int size) {

        std::string s ( size, ' ' );
        int shift = 2 * ( size - 1 );


        if ( text == ERROR_STR ) {
            s.assign( size, 'N' );
        }


        for ( int i = 0; i < size; i++, shift -= 2 ) {


            uint8_t character = (text >> shift) & 0x3;
            switch ( character ) {
                case 0: s[i] = 'A'; break;
                case 1: s[i] = 'C'; break;
                case 2: s[i] = 'G'; break;
                case 3: s[i] = 'T'; break;
                default: break;
            }
        }

        return s;
    }
