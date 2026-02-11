tds_put_buf(TDSSOCKET * tds, const unsigned char *buf, int dsize, int ssize)
{
	int cpsize;

	cpsize = ssize > dsize ? dsize : ssize;
	tds_put_n(tds, buf, cpsize);
	dsize -= cpsize;
	tds_put_n(tds, NULL, dsize);
	return tds_put_byte(tds, cpsize);
}
