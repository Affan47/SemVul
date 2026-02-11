ERR(const char *s, char c, char **argv)
{
	if(my_opterr)
	{
		char errbuf[2];
		errbuf[0] = c;
		errbuf[1] = '\n';


		(void) fwrite(argv[0], (unsigned)strlen(argv[0]),1,stderr);
		(void) fwrite(s, (unsigned)strlen(s),1,stderr);
		(void) fwrite(errbuf, 2, 1,stderr);
	}
}
