inputmode_ascii_get_previous_offset(GVInputModesData *imd, offset_type offset)
{
    char_type current_char, prev_char;

    if (offset>0)
        offset--;

    if (offset>0)
    {
        current_char = inputmode_ascii_get_char(imd, offset);
        if (current_char=='\n')
        {
            prev_char = inputmode_ascii_get_char(imd, offset-1);
            if (prev_char=='\r')
                offset--;
        }
    }

    return offset;
}
