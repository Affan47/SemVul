readonly_changable(struct tdb_context *tdb, const char *caller)
{
	if (inside_transaction(tdb)) {
		tdb->last_error = tdb_logerr(tdb, TDB_ERR_EINVAL,
					     TDB_LOG_USE_ERROR,
					     "%s: can't change"
					     " TDB_RDONLY inside transaction",
					     caller);
		return false;
	}
	return true;
}
