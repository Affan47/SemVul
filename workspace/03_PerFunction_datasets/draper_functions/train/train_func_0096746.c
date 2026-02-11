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


        if (dest == 0)
        {

        }
        else if (dest_len >= 2)
        {
            wchar_t unicode_char;


            unicode_char = src.getch();


            *dest++ = (unicode_char & 0xff);
            *dest++ = ((unicode_char >> 8) & 0xff);


            dest_len -= 2;
        }
        else
        {

            break;
        }


        cur_total += 2;
    }


    if (src_bytes_used != 0)
        *src_bytes_used = src.getptr() - src_start.getptr();


    return cur_total;
}
