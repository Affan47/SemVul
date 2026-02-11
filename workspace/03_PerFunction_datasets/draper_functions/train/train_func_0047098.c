__db_get_multiple(dbp)
	DB *dbp;
{
	DB_ILLEGAL_BEFORE_OPEN(dbp, "DB->get_multiple");


	return (dbp->type == DB_BTREE &&
	    F_ISSET(dbp, DB_AM_SUBDB) &&
	    dbp->meta_pgno == PGNO_BASE_MD ? 1 : 0);
}
