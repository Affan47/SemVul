decode(unsigned char *infile, int *a, int *nx, int *ny, int *scale)


{
LONGLONG sumall;
int nel, stat;
unsigned char nbitplanes[3];
char tmagic[2];

	;
	nextchar = 0;


	qread(infile, tmagic, sizeof(tmagic));


	if (memcmp(tmagic,code_magic,sizeof(code_magic)) != 0) {
		ffpmsg("bad file format");
		return(DATA_DECOMPRESSION_ERR);
	}
	*nx =readint(infile);
	*ny =readint(infile);
	*scale=readint(infile);

	nel = (*nx) * (*ny);


	sumall=readlonglong(infile);


	qread(infile, (char *) nbitplanes, sizeof(nbitplanes));

	stat = dodecode(infile, a, *nx, *ny, nbitplanes);


	a[0] = (int) sumall;
	return(stat);
}
