Ns_MySQL_DML(Ns_DbHandle *handle, char *sql)
{
    int             rc;

    assert(handle != NULL);
    assert(handle->connection != NULL);
    assert(sql != NULL);

    if (handle->verbose)
        Ns_Log(Notice, "Ns_MySQL_DML(%s) called.", handle->datasource);

    rc = mysql_query((MYSQL *) handle->connection, sql);
    Log(handle, (MYSQL *) handle->connection);

    if (rc) {
        return NS_ERROR;
    }

    return NS_OK;
}
