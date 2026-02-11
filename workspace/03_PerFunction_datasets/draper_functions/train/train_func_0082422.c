sqlite3_select(DBPoolConn *conn, const Octstr *sql)
{
    int res;
    const char *query_tail = NULL;
    sqlite3_stmt *stmt = NULL;

#if defined(SQLBOX_TRACE)
    debug("SQLBOX", 0, "sql: %s", octstr_get_cstr(sql));
#endif

    res = sqlite3_prepare_v2(conn->conn, octstr_get_cstr(sql), -1, &stmt, NULL);
    if (res != SQLITE_OK) {
        error(0, "SQLITE3: Could not compile query: %s", sqlite3_errmsg(conn->conn));
        return NULL;
    }
    return stmt;
}
