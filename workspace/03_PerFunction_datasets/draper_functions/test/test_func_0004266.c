getflag(CAP *cap, unsigned char *name)
{
#ifdef TERMINFO
	if (cap->abuf)
		return tgetflag((char *)name);
#endif
	return findcap(cap, name) != NULL;
}
