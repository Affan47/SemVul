dbm_fetch(db, key)
	DBM *db;
	datum key;
{
	datum retval;
	int status;

	status = (db->get)(db, (DBT *)&key, (DBT *)&retval, 0);
	if (status) {
		retval.dptr = NULL;
		retval.dsize = 0;
	}
	return (retval);
}
