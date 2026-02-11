reset_multis_before(filestruct *fileptr, int mindex)
{
    filestruct *oof;
    for (oof = fileptr->prev; oof != NULL; oof = oof->prev) {
	alloc_multidata_if_needed(oof);
	if (oof->multidata == NULL)
	    continue;
	if (oof->multidata[mindex] != CNONE)
	    oof->multidata[mindex] = -1;
	else
	    break;
    }
    for (; oof != NULL; oof = oof->prev) {
	alloc_multidata_if_needed(oof);
	if (oof->multidata == NULL)
	    continue;
	if (oof->multidata[mindex] == CNONE)
	    oof->multidata[mindex] = -1;
	else
	    break;
    }

    edit_refresh_needed = TRUE;
}
