sqlite_update(DBPoolConn *conn, const Octstr *sql)
{
    int state;
    char *errmsg = 0;


#if defined(SQLBOX_TRACE)
     debug("SQLBOX", 0, "sql: %s", octstr_get_cstr(sql));
#endif

    state = sqlite_exec(conn->conn, octstr_get_cstr(sql), NULL, 0, &errmsg);
    if (state != SQLITE_OK) {
        error(0, "SQLITE: %s", errmsg);
        return -1;
    }
    return sqlite_changes(conn->conn);
}
