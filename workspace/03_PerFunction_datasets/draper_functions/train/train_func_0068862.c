sdump(pagf)
int pagf;
{
	register b;
	register n = 0;
	register t = 0;
	register o = 0;
	register e;
	char pag[PBLKSIZ];

	while ((b = read(pagf, pag, PBLKSIZ)) > 0) {
		printf("#%d: ", n);
		if (!okpage(pag))
			printf("bad\n");
		else {
			printf("ok. ");
			if (!(e = pagestat(pag)))
			    o++;
			else
			    t += e;
		}
		n++;
	}

	if (b == 0)
		printf("%d pages (%d holes):  %d entries\n", n, o, t);
	else
		oops("read failed: block %d", n);
}
