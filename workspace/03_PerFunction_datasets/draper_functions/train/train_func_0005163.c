y_rsk(Void)
{
	if(f__curunit->uend || f__curunit->url <= f__recpos
		|| f__curunit->url == 1) return 0;
	do {
		getc(f__cf);
	} while(++f__recpos < f__curunit->url);
	return 0;
}
