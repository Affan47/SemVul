_db_get_id_by_name(sqlite3_stmt *stmt, const struct lms_string_size *name, int64_t *id)
{
    int r, ret;

    ret = lms_db_bind_text(stmt, 1, name->str, name->len);
    if (ret != 0)
        goto done;

    r = sqlite3_step(stmt);
    if (r == SQLITE_DONE) {
        ret = 1;
        goto done;
    }

    if (r != SQLITE_ROW) {
        fprintf(stderr, "ERROR: could not get id by name: %s\n",
                sqlite3_errmsg(sqlite3_db_handle(stmt)));
        ret = -2;
        goto done;
    }

    *id = sqlite3_column_int64(stmt, 0);
    ret = 0;

  done:
    lms_db_reset_stmt(stmt);

    return ret;

}
