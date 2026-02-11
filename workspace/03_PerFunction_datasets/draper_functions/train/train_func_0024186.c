print_xtext(FILE *fp, const char *xtext)
{
	while (*xtext)
	{
		if (*xtext != '+' || xtext[1] == 0 || xtext[2] == 0)
		{
			putc(*xtext, fp);
			xtext++;
		}
		else
		{
			putc( hexconvert(xtext[1], xtext[2]), fp);
			xtext += 3;
		}
	}
}
