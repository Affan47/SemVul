prevseq(Buffer *b)
{
	Undo u;
	uint up;

	up = b->nc;
	if(up == 0)
		return 0;
	up -= Undosize;
	bufread(b, up, (Rune*)&u, Undosize);
	return u.seq;
}
