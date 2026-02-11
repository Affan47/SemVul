output(c, fp, storepp)

char			c;
TFILE			*fp;
char			**storepp;

{
	int		returnval;


	if (fp == 0) {
		**storepp = c;
		++ (*storepp);
		returnval = c;
	}
	else {
		returnval = tputc(c, fp);
	}
	return(returnval);
}
