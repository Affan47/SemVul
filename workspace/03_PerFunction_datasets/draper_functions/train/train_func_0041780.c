put_iac_naws(byte c, int x, int y)
{
	if (G.iaclen + 9 > IACBUFSIZE)
		iac_flush();

	put_iac(IAC);
	put_iac(SB);
	put_iac(c);

	put_iac((x >> 8) & 0xff);
	put_iac(x & 0xff);
	put_iac((y >> 8) & 0xff);
	put_iac(y & 0xff);

	put_iac(IAC);
	put_iac(SE);
}
