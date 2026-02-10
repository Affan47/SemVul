at76_calc_padding(int wlen)
{

	wlen += AT76_TX_HDRLEN;

	wlen = wlen % 64;

	if (wlen < 50)
		return 50 - wlen;

	if (wlen >= 61)
		return 64 + 50 - wlen;

	return 0;
}
