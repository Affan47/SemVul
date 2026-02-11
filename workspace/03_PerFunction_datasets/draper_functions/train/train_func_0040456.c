pack6(n, last)
    register int	n;
    int			last;
{
    register char	*q;
    register int	i;
    char		b3[3];

    i = 3;
    if (last && (i = Buffer[n - 1]) >= 3) {

	(void)fprintf(stderr, "Badly-terminated file.\n");
	i = 3;
    }

    b3[0] = (Buffer[0] << 2) | ((Buffer[1] >> 4) & 0x03);
    b3[1] = (Buffer[1] << 4) | ((Buffer[2] >> 2) & 0x0F);
    b3[2] = (Buffer[2] << 6) | ( Buffer[3]       & 0x3F);
    for (q = b3; --i >= 0; )
	(void)putchar(*q++);
}
