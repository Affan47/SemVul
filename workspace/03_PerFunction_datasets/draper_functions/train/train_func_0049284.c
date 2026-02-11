get_region_id(region *reg) {
    char **line;
    char *sql;
    int nrow, ncolumn, id;

    if (!reg)
        return 0;

    sql = sqlite3_mprintf("select reg_id from region where reg_name='%q'", reg->name);
    sqlite3_get_table(logger_database, sql, &line, &nrow, &ncolumn, NULL);

    if (nrow > 0)
        id = atoi(line[ncolumn]);
    else {
        sqlite3_free(sql);
        sql = sqlite3_mprintf("insert into region(reg_name) values( '%q' )", reg->name);
        do_sql(sql, logger_database);
        id = sqlite3_last_insert_rowid(logger_database);
    }
    sqlite3_free(sql);
    sqlite3_free_table(line);
    return id;
}
