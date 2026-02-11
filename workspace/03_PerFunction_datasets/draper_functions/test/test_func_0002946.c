jgetstr(CAP *cap, unsigned char *name)
{
	struct sortentry *s;

#ifdef TERMINFO
	if (cap->abuf) {
		char *new_ptr = (char *)cap->abufp;
		char *rtn;
		rtn = tgetstr((char *)name, &new_ptr);
		cap->abufp = (unsigned char *)new_ptr;
		return (unsigned char *)rtn;
	}
#endif
	s = findcap(cap, name);
	if (s)
		return s->value;
	else
		return NULL;
}
