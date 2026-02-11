ReadPackedInt32 (FILE *file, const char *fname)
{
    Unsigned32_t	n;
    Byte_t		c;

    n = 0;
    do {
	ReadBinFile (file, &c, sizeof(c), fname);
	n = (n << 7) | (c & 0x7f);
    } while ((c & 0x80) != 0);

    return ((Int32_t)n);

}
