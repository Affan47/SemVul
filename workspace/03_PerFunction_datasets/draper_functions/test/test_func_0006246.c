w_cmd(File *f, Cmd *cp)
{
	int fseq;

	fseq = f->seq;
	if(getname(f, cp->ctext, FALSE)==0)
		error(Enoname);
	if(fseq == seq)
		error_s(Ewseq, genc);
	writef(f);
	return TRUE;
}
