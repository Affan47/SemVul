TlistReplace( Tlist *tlist, Geom *geom )
{
    Geom *old;

    if(tlist == NULL)
	return NULL;

    old = tlist->tlist;
    tlist->tlist = geom;
    return old;
}
