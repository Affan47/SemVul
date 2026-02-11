duplrlist(rp)
redirectlist *rp;
{
	redirectlist *new, *next;
	char *filename;

	if (!rp) return(NULL);
	next = duplrlist(rp -> next);
	if (rp -> type & MD_HEREDOC)
		filename = (char *)duplheredoc((heredoc_t *)(rp -> filename));
	else filename = Xstrdup(rp -> filename);
	new = newrlist(rp -> fd, filename, rp -> type | MD_DUPL, next);
	new -> new = rp -> new;
	new -> old = rp -> old;
#ifdef	DEP_DOSDRIVE
	new -> fakepipe = rp -> fakepipe;
	new -> dosfd = rp -> dosfd;
#endif

	return(new);
}
