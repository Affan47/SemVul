UpdateDelay(CONSENT *pCE)
#else
UpdateDelay(pCE)
    CONSENT *pCE;
#endif
{
    char *l;
    struct delay *d;

    if (pCE->host != (char *)0)
	l = pCE->host;
    else
	l = "";

    for (d = delays; d != (struct delay *)0; d = d->next) {
	if (strcmp(l, d->host) == 0) {
	    d->last = time((time_t *)0);
	    return;
	}
    }
    if ((d =
	 (struct delay *)malloc(sizeof(struct delay))) ==
	(struct delay *)0)
	OutOfMem();
    if ((d->host = StrDup(l)) == (char *)0)
	OutOfMem();
    d->last = time((time_t *)0);
    d->next = delays;
    delays = d;
}
