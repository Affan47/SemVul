os_parse_chars (unsigned char *buf, glui32 buflen,
                       glui32 *out, glui32 outlen)
{
    switch (os_charmap)
    {
        case OS_UTF8:
            return parse_utf8(buf, buflen, out, outlen);

        case OS_CP1251:
            return parse_cp1251(buf, buflen, out, outlen);

        case OS_CP1252:
            return parse_cp1252(buf, buflen, out, outlen);

        case OS_MACROMAN:
            return parse_mac(buf, buflen, out, outlen);

        default:
            return 0;
    }
}
