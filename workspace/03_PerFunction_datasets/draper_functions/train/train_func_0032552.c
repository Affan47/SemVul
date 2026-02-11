_utf32_to_utf8( const unicode_char& in_uc, unsigned char out_cp[6] )
    {
        size_t len = _utf8_char_length( in_uc );
        unicode_char c = in_uc;


        for ( size_t i = len - 1; i > 0; i-- ) {
            out_cp[i] = static_cast<unsigned char>((( c ) & _cont_mask ) | _cont);
            c >>= 6;
        }


        switch ( len ) {
            case 6:
                out_cp[0] = static_cast<unsigned char>((( c ) & _lead5_mask ) | _lead5);
                break;
            case 5:
                out_cp[0] = static_cast<unsigned char>((( c ) & _lead4_mask ) | _lead4);
                break;
            case 4:
                out_cp[0] = static_cast<unsigned char>((( c ) & _lead3_mask ) | _lead3);
                break;
            case 3:
                out_cp[0] = static_cast<unsigned char>((( c ) & _lead2_mask ) | _lead2);
                break;
            case 2:
                out_cp[0] = static_cast<unsigned char>((( c ) & _lead1_mask ) | _lead1);
                break;
            case 1:
            default:
                out_cp[0] = static_cast<unsigned char>(( c ) & 0x7F);
                break;
        }


        return len;
    }
