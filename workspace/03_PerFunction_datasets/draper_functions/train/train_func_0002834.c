FontLoadw(fp, fsize)
FILE	*fp;
size_t	fsize;
{
    size_t	start;
    int	addr, k1, k2, i;
    u_char	*fontbuf;

    fi.size = get_kfontoft((MAXKANJI+1)>>8, (MAXKANJI+1) & 0xFF);
    start = get_kfontoft((MINKANJI)>>8, (MINKANJI) & 0xFF);
    if ((fontbuf = (u_char *)malloc(fi.size)) == NULL) return(NULL);
    for (k1 = 0x21; k1 <= 0x74; k1 ++) {
	for (k2 = 0x21; k2 < 0x7f; k2 ++) {
	    if (k1 > 0x29 && k1 < 0x30) {
		for (i = 0; i < fsize; i ++) fgetc(fp);

		continue;
	    }
	    addr = get_kfontoft(k1, k2);
	    if (fread(fontbuf + addr, fsize, 1, fp) != 1)
		return(NULL);
	    if(k1 == 0x74 && k2 == 0x24) break;
	}
    }
    return(fontbuf + start);
}
