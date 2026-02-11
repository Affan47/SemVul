WriteBytesSwapped(FILE * fp, char *p, int n)
{
    p += n - 1;
    while (n-- > 0)
        putc(*p--, fp);
}
