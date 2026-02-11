ReadBytes(FILE * fp, char *p, int n)
{


    while (!feof(fp) & (n-- > 0))
        *p++ = getc(fp);
}
