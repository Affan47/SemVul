mkitaijitbl()
{
    FILE *fp;
    int i, j;
    char buffer[BUFSIZE];
    unsigned char n1, n2, o1, o2;
    char *itaijidictpath;

    itaijidictpath = (char*)getenv("ITAIJIDICTPATH");
    if (itaijidictpath == (char*)NULL)
	itaijidictpath = (char*)getenv("ITAIJIDICT");
    if (itaijidictpath == (char*)NULL)
	itaijidictpath = ITAIJIDICT;

    if ((fp = fopen(itaijidictpath, "rb")) == NULL) {
	fprintf(stderr, "Can't open Kanji itaijidict file ");
	perror(itaijidictpath);
	exit(0);
    }
    for (i = 0; i < 0x80; ++ i) {
	for (j = 0; j < 0x80; ++ j) {
	    ittbl1[i][j] = i | 0x80;
	    ittbl2[i][j] = j | 0x80;
	}
    }
    while(fgets(buffer, BUFSIZE, fp) != NULL) {
	n1 = buffer[0];
	n2 = buffer[1];
	o1 = buffer[2];
	o2 = buffer[3];
	n1 &= 0x7f;
	n2 &= 0x7f;
	ittbl1[n1][n2] = o1;
	ittbl2[n1][n2] = o2;
    }
    fclose(fp);
}
