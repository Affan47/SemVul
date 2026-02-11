contains_ssn(const unsigned char *buffer, int length, int format, int detmode)
{
    const unsigned char *idx;
    const unsigned char *end;
    int count = 0;

    if(buffer == NULL || length < 9)
        return 0;

    end = buffer + length;
    idx = buffer;
    while(idx < end)
    {
        if(isdigit(*idx))
        {

            if((idx == buffer || !isdigit(idx[-1])) && dlp_is_valid_ssn(idx, length - (idx - buffer), format) == 1)
            {
                if(detmode == DETECT_MODE_COUNT)
                {
                    count++;

                    idx += ((format == SSN_FORMAT_HYPHENS)?11:9);
                }
                else
                {
                    return 1;
                }
            }
        }
        idx++;
    }

    return count;
}
