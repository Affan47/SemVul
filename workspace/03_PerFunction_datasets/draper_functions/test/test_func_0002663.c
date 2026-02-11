updatedirtime (a_inode *a1, int now)
{
	struct mystat statbuf;

	if (!a1->parent)
		return;
#ifdef FSUAE
	if (!a1->parent->parent) {
	    return;
	}
#endif
	if (!now) {
		if (!my_stat (a1->nname, &statbuf))
			return;
		my_utime (a1->parent->nname, &statbuf.mtime);
	} else {
	    my_utime (a1->parent->nname, NULL);
	}
}
