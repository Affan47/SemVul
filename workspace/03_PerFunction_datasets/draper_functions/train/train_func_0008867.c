_ar_sqlite_create_user(authreg_t ar, char *username, char *realm)
{
    sqlite3_stmt *stmt;
    moddata_t data = data = (moddata_t) ar->private;
    int res, ret = 0;

    char *sql =
	"INSERT INTO authreg ( username, realm ) VALUES ( ?, ? )";

    log_debug(ZONE, "sqlite (authreg): create user");

    stmt = _get_stmt(ar, data->db, &data->create_user_stmt, sql);
    if (stmt == NULL) {
	return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, realm, -1, SQLITE_STATIC);

    res = sqlite3_step(stmt);
    if (res != SQLITE_DONE) {
	log_write(ar->c2s->log, LOG_ERR, "sqlite (authreg): %s", sqlite3_errmsg (data->db));
	ret = 1;
    }
    sqlite3_reset(stmt);
    return 0;
}
