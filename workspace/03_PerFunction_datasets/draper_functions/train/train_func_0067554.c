lcdm001_chr (Driver *drvthis, int x, int y, char c)
{
	PrivateData *p = drvthis->private_data;

	y--; x--;

	if ((x >= 0) && (y >= 0) && (x < p->width) && (y < p->height))
		p->framebuf[(y * p->width) + x] = c;

	debug(RPT_DEBUG, "LCDM001: writing character %02X to position (%d,%d)", c, x, y);
}
