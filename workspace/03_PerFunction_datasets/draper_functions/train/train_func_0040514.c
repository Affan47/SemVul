__ram_set_flags(dbp, flagsp)
	DB *dbp;
	u_int32_t *flagsp;
{
	u_int32_t flags;

	flags = *flagsp;
	if (LF_ISSET(DB_RENUMBER | DB_SNAPSHOT)) {
		DB_ILLEGAL_AFTER_OPEN(dbp, "DB->set_flags");
		DB_ILLEGAL_METHOD(dbp, DB_OK_RECNO);
	}

	__ram_map_flags(dbp, flagsp, &dbp->flags);
	return (0);
}
