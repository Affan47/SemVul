__bam_31_btreemeta(dbp, real_name, flags, fhp, h, dirtyp)
	DB *dbp;
	char *real_name;
	u_int32_t flags;
	DB_FH *fhp;
	PAGE *h;
	int *dirtyp;
{
	BTMETA30 *oldmeta;
	BTMETA31 *newmeta;

	COMPQUIET(dbp, NULL);
	COMPQUIET(real_name, NULL);
	COMPQUIET(fhp, NULL);

	newmeta = (BTMETA31 *)h;
	oldmeta = (BTMETA30 *)h;


	newmeta->root = oldmeta->root;
	newmeta->re_pad = oldmeta->re_pad;
	newmeta->re_len = oldmeta->re_len;
	newmeta->minkey = oldmeta->minkey;
	newmeta->maxkey = oldmeta->maxkey;
	memmove(newmeta->dbmeta.uid,
	    oldmeta->dbmeta.uid, sizeof(oldmeta->dbmeta.uid));
	newmeta->dbmeta.flags = oldmeta->dbmeta.flags;
	newmeta->dbmeta.record_count = 0;
	newmeta->dbmeta.key_count = 0;
	ZERO_LSN(newmeta->dbmeta.unused3);


	newmeta->dbmeta.version = 8;


	if (LF_ISSET(DB_DUPSORT))
		F_SET(&newmeta->dbmeta, BTM_DUPSORT);

	*dirtyp = 1;
	return (0);
}
