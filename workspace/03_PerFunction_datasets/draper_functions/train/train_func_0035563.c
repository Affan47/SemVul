s_wdue(cilist *a)
#endif
{
	int n;
	f__reading=0;
	if(n=c_due(a)) return(n);
	if(f__curunit->uwrt != 1 && f__nowwriting(f__curunit))
		err(a->cierr,errno,"write start");
	return(0);
}
