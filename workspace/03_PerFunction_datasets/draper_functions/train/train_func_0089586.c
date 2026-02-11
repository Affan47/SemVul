gline(char *buf)
{
	char *p;

	p = Brdline(&fin, '\n');
	if(p == 0)
		return 1;
	if(fin.rdline >= bsize-1) {
		fprint(2, "line too long\n");
		exits("too long");
	}
	memmove(buf, p, fin.rdline);
	buf[fin.rdline-1] = 0;
	return 0;
}
