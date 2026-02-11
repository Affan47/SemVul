_dwarf_decode_u_leb128_chk(Dwarf_Small * leb128, Dwarf_Word * leb128_length,
    Dwarf_Unsigned *outval,Dwarf_Byte_Ptr endptr)
{
    unsigned char byte     = 0;
    Dwarf_Word word_number = 0;
    Dwarf_Unsigned number  = 0;
    Dwarf_Sword shift      = 0;

    unsigned byte_length   = 0;

    if (leb128 >=endptr) {
        return DW_DLV_ERROR;
    }


    if ((*leb128 & 0x80) == 0) {
        if (leb128_length) {
            *leb128_length = 1;
        }
        *outval = *leb128;
        return DW_DLV_OK;
    } else {
        if ((leb128+1) >=endptr) {
            return DW_DLV_ERROR;
        }
        if ((*(leb128 + 1) & 0x80) == 0) {
            if (leb128_length) {
                *leb128_length = 2;
            }
            word_number = *leb128 & 0x7f;
            word_number |= (*(leb128 + 1) & 0x7f) << 7;
            *outval = word_number;
            return DW_DLV_OK;
        }

    }


    number = 0;
    shift = 0;
    byte_length = 1;
    byte = *leb128;
    for (;;) {
        number |= ((Dwarf_Unsigned) (byte & 0x7f)) << shift;

        if ((byte & 0x80) == 0) {
            if (leb128_length) {
                *leb128_length = byte_length;
            }
            *outval = number;
            return DW_DLV_OK;
        }
        shift += 7;

        byte_length++;
        if (byte_length > BYTESLEBMAX) {

            if( leb128_length) {
                *leb128_length = BYTESLEBMAX;
            }
            break;
        }
        ++leb128;
        if ((leb128) >=endptr) {
            return DW_DLV_ERROR;
        }
        byte = *leb128;
    }
    return DW_DLV_ERROR;
}
