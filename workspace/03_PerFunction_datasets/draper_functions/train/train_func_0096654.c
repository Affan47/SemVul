drv_CF_write2(const int row, const int col, const char *data, const int len)
{
    int l = len;


    if (col + l > 16)
	l = 16 - col;
    if (l < 0)
	l = 0;


    if (row >= 2 || col + l > 16) {
	error("%s: internal error: write outside linebuffer bounds!", Name);
	return;
    }
    memcpy(Line + 16 * row + col, data, l);
    drv_CF_send(7 + row, 16, (unsigned char *) (Line + 16 * row));
}
