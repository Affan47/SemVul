enc_file_uue(PostAttachment *pa, FILE *fin, FILE *fout)
{
    char	*name = pa->name;
    char	buf[45];
    int		n;

    if (!name) {
	name = strrchr(pa->file_name, '/');
	if (name)
	    name++;
	else
	    name = pa->file_name;
    }

    fprintf(fout, "begin 0644 %s\r\n", name);

#if 0
#  define UU_CHAR(a)  ((unsigned char)(' ' + ((a) & 0x3fu)))
#else
#  define UU_CHAR(a)  ((unsigned char)(' ' + 1 + (((a) - 1) & 0x3fu)))
#endif

    while ((n = fread(buf, 1, sizeof buf, fin)) > 0) {
	unsigned long	acc;
	unsigned char	*c = (unsigned char *)buf;

	if (' ' + n == '.')
	    putc('.', fout);
	putc(' ' + n, fout);
	while (n > 2) {
	    acc = (c[0] << 16) | (c[1] << 8) | c[2];
	    fprintf(fout, "%c%c%c%c",
		    UU_CHAR(acc >> 18), UU_CHAR(acc >> 12),
		    UU_CHAR(acc >>  6), UU_CHAR(acc      ));


	    n -= 3;
	    c += 3;
	}

	switch (n) {
	case 1:
	    acc = c[0] << 16;
	    fprintf(fout, "%c%c", UU_CHAR(acc >> 18), UU_CHAR(acc >> 12));


	    break;
	case 2:
	    acc = (c[0] << 16) | (c[1] << 8);
	    fprintf(fout, "%c%c%c",
		    UU_CHAR(acc >> 18), UU_CHAR(acc >> 12), UU_CHAR(acc >> 6));


	    break;
	}

	fputs("\r\n", fout);
    }

    fputs("`\r\nend\r\n\r\n", fout);

    return True;
}
