utf8_is_valid_char(GVInputModesData *imd, offset_type offset)
{
    int len = utf8_get_char_len(imd, offset);

    if (len==0 || (gv_input_mode_get_byte(imd, offset+len)==INVALID_CHAR))
        return FALSE;

    if (len==1)
        return TRUE;

    if (!UTF8_TRAILER_CHAR(gv_input_mode_get_byte(imd, offset+1)))
        return FALSE;

    if (len==2)
        return TRUE;

    if (!UTF8_TRAILER_CHAR(gv_input_mode_get_byte(imd, offset+2)))
        return FALSE;

    if (len==3)
        return TRUE;

    if (!UTF8_TRAILER_CHAR(gv_input_mode_get_byte(imd, offset+3)))
        return FALSE;

    if (len==4)
        return TRUE;

    return FALSE;
}
