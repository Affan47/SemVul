lms_db_end_transaction(sqlite3_stmt *stmt)
{
    int r, ret;

    ret = 0;
    r = sqlite3_step(stmt);
    if (r != SQLITE_DONE) {
        fprintf(stderr, "ERROR: could not end transaction: %s\n",
                sqlite3_errmsg(sqlite3_db_handle(stmt)));
        ret = -1;
    }

    r = sqlite3_reset(stmt);
    if (r != SQLITE_OK)
        fprintf(stderr, "ERROR: could not reset SQL statement: %s\n",
                sqlite3_errmsg(sqlite3_db_handle(stmt)));

    return ret;
}
