map_utf8(char *dest, size_t dest_len,
                                   utf8_ptr src, size_t src_byte_len,
                                   size_t *src_bytes_used) const
{
    utf8_ptr src_start;
    size_t cur_total;
    char *srcend;


    src_start = src;


    srcend = src.getptr() + src_byte_len;


    for (cur_total = 0 ; src.getptr() < srcend ; src.inc())
    {
        const unsigned char *mapping;
        size_t map_len;


        mapping = get_xlation(src.getch(), &map_len);


        if (dest == 0)
        {

        }
        else if (map_len <= dest_len)
        {

            memcpy(dest, mapping, map_len);


            dest += map_len;
            dest_len -= map_len;
        }
        else
        {

            break;
        }


        cur_total += map_len;
    }


    if (src_bytes_used != 0)
        *src_bytes_used = src.getptr() - src_start.getptr();


    return cur_total;
}
