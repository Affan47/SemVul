_dxfdeletedict(struct dict *d)
{
    struct localstor *ls, *next;

    if (!d)
	return ERROR;

    if (d->dicttab) {
	DXDestroyHash(d->dicttab);
	d->dicttab = NULL;
    }

    if (d->keytab) {
	DXDestroyHash(d->keytab);
	d->keytab = NULL;
    }

    ls = d->localdict;
    while(ls) {
	next = ls->next;
	DXFree((Pointer)ls);
	ls = next;
    }

    d->localdict = NULL;
    d->nextid = BADINDEX;

    return OK;
}
