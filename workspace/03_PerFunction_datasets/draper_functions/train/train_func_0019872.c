sdbm_unlink(DBM *db)
{
	if G_UNLIKELY(db == NULL)
		return;

	sdbm_close_internal(db, TRUE, TRUE);
}
