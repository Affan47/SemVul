do_decode(struct rfc2045 *p, struct rfc2045id *id, void *ptr)
{
struct rfc2045findstruct *fs=(struct rfc2045findstruct *)ptr;
const char *partnum=fs->partnum;
unsigned n;

	while (id)
	{
		if (!isdigit((int)(unsigned char)*partnum))	return;
		n=0;
		while (isdigit((int)(unsigned char)*partnum))
			n=n*10 + *partnum++ - '0';
		if (*partnum)
		{
			if (*partnum != '.')	return;
			++partnum;
		}
		if (n != (unsigned)id->idnum)	return;
		id=id->next;
	}
	if ( *partnum == '\0')	fs->ptr=p;
}
