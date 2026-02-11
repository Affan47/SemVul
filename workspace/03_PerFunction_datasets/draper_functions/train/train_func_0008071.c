jgetstr(CAP *cap, unsigned char *name)
{
	struct sortentry *s;

#ifdef TERMINFO
	if (cap->abuf)
		return (unsigned char *)tgetstr((char *)name, (char **)&cap->abufp);
#endif
	s = findcap(cap, name);
	if (s)
		return s->value;
	else
		return NULL;
}
