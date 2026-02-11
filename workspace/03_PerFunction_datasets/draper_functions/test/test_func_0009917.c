t4_tx_put_fax_header(t4_state_t *s)
{
    int row;
    int i;
    int repeats;
    int pattern;
    int row_bufptr;
    char *t;
    char header[132 + 1];


    make_header(s, header);
    switch (s->y_resolution)
    {
    case T4_Y_RESOLUTION_1200:
        repeats = 12;
        break;
    case T4_Y_RESOLUTION_800:
        repeats = 8;
        break;
    case T4_Y_RESOLUTION_600:
        repeats = 6;
        break;
    case T4_Y_RESOLUTION_SUPERFINE:
        repeats = 4;
        break;
    case T4_Y_RESOLUTION_300:
        repeats = 3;
        break;
    case T4_Y_RESOLUTION_FINE:
        repeats = 2;
        break;
    default:
        repeats = 1;
        break;
    }
    for (row = 0;  row < 16;  row++)
    {
        t = header;
        row_bufptr = 0;
        for (t = header;  *t  &&  row_bufptr <= s->bytes_per_row - 2;  t++)
        {
            pattern = header_font[(uint8_t) *t][row];
            s->row_buf[row_bufptr++] = (uint8_t) (pattern >> 8);
            s->row_buf[row_bufptr++] = (uint8_t) (pattern & 0xFF);
        }
        for (  ;  row_bufptr < s->bytes_per_row;  )
            s->row_buf[row_bufptr++] = 0;
        for (i = 0;  i < repeats;  i++)
        {
            if (encode_row(s))
                return -1;
        }
    }
    return 0;
}
