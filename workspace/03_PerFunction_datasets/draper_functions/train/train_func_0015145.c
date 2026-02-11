__ham_31_hashmeta(dbp, real_name, flags, fhp, h, dirtyp)
	DB *dbp;
	char *real_name;
	u_int32_t flags;
	DB_FH *fhp;
	PAGE *h;
	int *dirtyp;
{
	HMETA30 *oldmeta;
	HMETA31 *newmeta;

	COMPQUIET(dbp, NULL);
	COMPQUIET(real_name, NULL);
	COMPQUIET(fhp, NULL);

	newmeta = (HMETA31 *)h;
	oldmeta = (HMETA30 *)h;


	memmove(newmeta->spares, oldmeta->spares, sizeof(oldmeta->spares));
	newmeta->h_charkey = oldmeta->h_charkey;
	newmeta->nelem = oldmeta->nelem;
	newmeta->ffactor = oldmeta->ffactor;
	newmeta->low_mask = oldmeta->low_mask;
	newmeta->high_mask = oldmeta->high_mask;
	newmeta->max_bucket = oldmeta->max_bucket;
	memmove(newmeta->dbmeta.uid,
	    oldmeta->dbmeta.uid, sizeof(oldmeta->dbmeta.uid));
	newmeta->dbmeta.flags = oldmeta->dbmeta.flags;
	newmeta->dbmeta.record_count = 0;
	newmeta->dbmeta.key_count = 0;
	ZERO_LSN(newmeta->dbmeta.unused3);


	newmeta->dbmeta.version = 7;


	if (LF_ISSET(DB_DUPSORT))
		F_SET(&newmeta->dbmeta, DB_HASH_DUPSORT);

	*dirtyp = 1;
	return (0);
}
