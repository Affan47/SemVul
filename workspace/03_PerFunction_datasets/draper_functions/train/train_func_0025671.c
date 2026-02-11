NGfind(const char *Name)
{
    const char		*p;
    int			i;
    unsigned int	j;
    NEWSGROUP		**ngp;
    char		c;
    NGHASH		*htp;

    NGH_HASH(Name, p, j);
    htp = NGH_BUCKET(j);
    for (c = *Name, ngp = htp->Groups, i = htp->Used; --i >= 0; ngp++)
	if (c == ngp[0]->Name[0] && strcmp(Name, ngp[0]->Name) == 0)
	    return ngp[0];
    return NULL;
}
