put_sugtime(spin, fd)
    spellinfo_T *spin;
    FILE	*fd;
{
    int		c;
    int		i;


    for (i = 7; i >= 0; --i)
	if (i + 1 > sizeof(time_t))

	    putc(0, fd);
	else
	{
	    c = (unsigned)spin->si_sugtime >> (i * 8);
	    putc(c, fd);
	}
}
