get_valuedata(uint64 dbkey)
{
	struct valuedata *vd;

	vd = dbmw_read(db_valuedata, &dbkey, NULL);

	if (vd == NULL) {
		if (dbmw_has_ioerr(db_valuedata)) {
			g_warning("DBMW \"%s\" I/O error, bad things could happen...",
				dbmw_name(db_valuedata));
		} else {
			g_warning("value for DB-key %s exists but not found in DBMW \"%s\"",
				uint64_to_string(dbkey), dbmw_name(db_valuedata));
		}
		return NULL;
	}

	return vd;
}
