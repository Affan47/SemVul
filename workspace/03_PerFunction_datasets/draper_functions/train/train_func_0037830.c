sdbm_name(DBM *db)
{
	sdbm_check(db);

	return db->name ? db->name : "";
}
