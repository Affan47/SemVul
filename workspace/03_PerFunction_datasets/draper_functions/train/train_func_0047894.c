_dxfinitdict(struct dict *d)
{
    if (!d)
        return ERROR;

    d->dicttab = DXCreateHash(sizeof(struct dinfo), NULL, hashCompare);
    if (!d->dicttab)
	goto error;

    d->keytab = DXCreateHash(sizeof(struct kinfo), NULL, hashCompare);
    if (!d->keytab)
	goto error;

    d->localdict = (struct localstor *)
	           DXAllocateLocalZero(sizeof(struct localstor));
    if (!d->localdict)
	goto error;

    d->localdict->nextbyte = 0;
    d->localdict->bytesleft = LOCALSTORBLOCK;
    d->localdict->next = NULL;

    d->nextid = 1;

    if (!initkeywords(d))
	goto error;

    return OK;

  error:
    _dxfdeletedict(d);
    return ERROR;
}
