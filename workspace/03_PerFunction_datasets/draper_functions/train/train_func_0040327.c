AllBlack(f, wid, hei)
char *f;
int wid, hei;
{
	if (wid > 3)
	{
		wid /= 2;
		hei /= 2;
		return (AllBlack(f, wid, hei) && AllBlack(f + wid, wid, hei) &&
		  AllBlack(f + WIDTH * hei, wid, hei) &&
		  AllBlack(f + WIDTH * hei + wid, wid, hei));
	}
	else
		return (*f || *(f + 1) || *(f + WIDTH) || *(f + WIDTH + 1));
}
