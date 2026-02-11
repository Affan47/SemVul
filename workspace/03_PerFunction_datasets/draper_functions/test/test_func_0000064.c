Ns_PgTableList(Ns_DString *pds, Ns_DbHandle *handle, int fSystemTables) {

    static char *asfuncname = "Ns_PgTableList";
    Ns_Set         *row;
    Ns_DString      ds;
    char           *table;
    int             status = NS_ERROR;

    if (pds == NULL) {
        Ns_Log(Error, "%s: Invalid Ns_DString -> pds.", asfuncname);
        goto done;
    }

    if (handle == NULL || handle->connection == NULL) {
        Ns_Log(Error, "%s: Invalid connection.", asfuncname);
        goto done;
    }

    Ns_DStringInit(&ds);
    Ns_DStringAppend(&ds, "SELECT relname FROM pg_class "
                     "WHERE relkind = 'r' and relname !~ '^Inv' ");
    if (!fSystemTables) {
        Ns_DStringAppend(&ds, "and relname !~ '^pg_' ");
    }
    Ns_DStringAppend(&ds, "ORDER BY relname");
    row = Ns_PgSelect(handle, ds.string);
    Ns_DStringFree(&ds);

    if (row != NULL) {
        while ((status = Ns_DbGetRow(handle, row)) == NS_OK) {
            table = row->fields[0].value;
            if (table == NULL) {
                Ns_Log(Warning, "Ns_PgTableList(%s):  NULL relname in 'pg_class' table.",
                       handle->datasource);
            } else {
                Ns_DStringNAppend(pds, table, strlen(table) + 1);
            }
        }
    }
    if (status == NS_END_DATA) {
        return (pds->string);
    }
  done:
    return (NULL);
}
