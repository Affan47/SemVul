sdb_FindObjectsFinal(SDB *sdb, SDBFind *sdbFind)
{
    SDBPrivate *sdb_p = sdb->private;
    sqlite3_stmt *stmt = sdbFind->findstmt;
    sqlite3 *sqlDB = sdbFind->sqlDB;
    int sqlerr = SQLITE_OK;

    LOCK_SQLITE()
    if (stmt) {
	sqlite3_reset(stmt);
	sqlerr = sqlite3_finalize(stmt);
    }
    if (sqlDB) {
	sdb_closeDBLocal(sdb_p, sqlDB) ;
    }
    PORT_Free(sdbFind);

    UNLOCK_SQLITE()
    return sdb_mapSQLError(sdb_p->type, sqlerr);
}
