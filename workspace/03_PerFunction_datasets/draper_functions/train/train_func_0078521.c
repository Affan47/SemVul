readlibdir(lp)
    library *lp;
{
    int i;
    char *sp;
    long liboffset, totalsize;

    if (fscanf(lp->fdata, "%ld %ld %ld %ld %ld\n",
	    &lp->rev,&lp->nentries,&lp->strsize,&liboffset,&totalsize) != 5)
	return FALSE;
    if (lp->rev > DLB_MAX_VERS || lp->rev < DLB_MIN_VERS) return FALSE;

    lp->dir = (libdir *) alloc(lp->nentries * sizeof(libdir));
    lp->sspace = (char *) alloc(lp->strsize);


    for (i = 0, sp = lp->sspace; i < lp->nentries; i++) {
	lp->dir[i].fname = sp;
	if (fscanf(lp->fdata, "%c%s %ld\n",
			&lp->dir[i].handling, sp, &lp->dir[i].foffset) != 3) {
	    free((genericptr_t) lp->dir);
	    free((genericptr_t) lp->sspace);
	    lp->dir = (libdir *) 0;
	    lp->sspace = (char *) 0;
	    return FALSE;
	}
	sp = eos(sp) + 1;
    }


    for (i = 0; i < lp->nentries; i++) {
	if (i == lp->nentries - 1)
	    lp->dir[i].fsize = totalsize - lp->dir[i].foffset;
	else
	    lp->dir[i].fsize = lp->dir[i+1].foffset - lp->dir[i].foffset;
    }

    (void) fseek(lp->fdata, 0L, SEEK_SET);
    lp->fmark = 0;

    return TRUE;
}
