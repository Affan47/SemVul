cl_tcscasefold( TCHAR * str, int len )
{
    TCHAR *p = str;
    while ((len < 0 || p < str + len) && *p)
    {
        *p = cl_tcasefold(*p);
		p++;
    }
    return str;
}
