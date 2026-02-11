print_coord2(stream * s, floatp x, floatp y, const char *str)
{
    pprintg2(s, "%g %g ", round_coord2(x), round_coord2(y));
    if (str != 0)
        stream_puts(s, str);
}
