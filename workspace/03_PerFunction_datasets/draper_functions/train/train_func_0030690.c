prev_ifile(h)
	IFILE h;
{
	register struct ifile *p;

	p = (h == NULL_IFILE) ? &anchor : int_ifile(h);
	if (p->h_prev == &anchor)
		return (NULL_IFILE);
	return (ext_ifile(p->h_prev));
}
