arglen(char *src, char *sep, int arg, int opt)
{
	arg_t s;
	size_t l;
	int r;

	argopts(&s, src, sep, opt);

	l = 0;

	while((r = arggetc(&s)) != ARG_EOS)
	{
		if(r == ARG_EOA)
		{
			if(!(opt & ARG_NO_TRIM) && !l) continue;
			if(!arg--) return(l);

			l = 0;

			continue;
		}

		l++;
	}

	if(!arg && !(!(opt & ARG_NO_TRIM) && !l)) return(l);

	return(-1);
}
