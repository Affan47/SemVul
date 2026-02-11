nowrap_align_offset(GVDataPresentation *dp, offset_type offset)
{
    while (offset>0)
    {
        char_type value = gv_input_mode_get_utf8_char(dp->imd, offset);
        if (value==INVALID_CHAR)
            return 0;
        if (value=='\r' || value=='\n')
            break;
        offset = gv_input_get_previous_char_offset(dp->imd, offset);
    }
    if (offset>0)
        return gv_input_get_next_char_offset(dp->imd, offset);
    return 0;
}
