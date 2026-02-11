dlr_mysql_messages(void)
{
    Octstr *sql;
    long res;
    MYSQL_RES *result;
    MYSQL_ROW row;

    sql = octstr_format("SELECT count(*) FROM %s;", octstr_get_cstr(fields->table));

    result = mysql_select(sql);
    octstr_destroy(sql);

    if (result == NULL) {
        return -1;
    }
    if (mysql_num_rows(result) < 1) {
        debug("dlr.mysql", 0, "Could not get count of DLR table");
        mysql_free_result(result);
        return 0;
    }
    row = mysql_fetch_row(result);
    if (row == NULL) {
        debug("dlr.mysql", 0, "rows found but could not load them");
        mysql_free_result(result);
        return 0;
    }
    res = atol(row[0]);
    mysql_free_result(result);

    return res;
}
