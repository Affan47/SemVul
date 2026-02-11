chancreate(int elemsize, int bufsize)
{
	Channel *c;

	c = malloc(sizeof *c+bufsize*elemsize);
	if(c == nil){
		fprint(2, "chancreate malloc: %r");
		exit(1);
	}
	memset(c, 0, sizeof *c);
	c->elemsize = elemsize;
	c->bufsize = bufsize;
	c->nbuf = 0;
	c->buf = (uchar*)(c+1);
	return c;
}
