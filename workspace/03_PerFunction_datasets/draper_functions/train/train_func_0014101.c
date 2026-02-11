display(File *f)
{
	Posn p1, p2;
	int np;
	char *c;

	p1 = addr.r.p1;
	p2 = addr.r.p2;
	if(p2 > f->b.nc){
		fprint(2, "bad display addr p1=%ld p2=%ld f->b.nc=%d\n", p1, p2, f->b.nc);
		p2 = f->b.nc;
	}
	while(p1 < p2){
		np = p2-p1;
		if(np>BLOCKSIZE-1)
			np = BLOCKSIZE-1;
		bufread(&f->b, p1, genbuf, np);
		genbuf[np] = 0;
		c = Strtoc(tmprstr(genbuf, np+1));
		if(downloaded)
			termwrite(c);
		else
			Write(1, c, strlen(c));
		free(c);
		p1 += np;
	}
	f->dot = addr;
	return TRUE;
}
