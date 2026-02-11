espUpdateFields(HttpConn *conn, cchar *tableName, MprHash *params)
{
    EdiRec  *rec;

    if ((rec = espSetFields(espReadRec(conn, tableName), params)) == 0) {
        return 0;
    }
    return ediUpdateRec(espGetDatabase(conn), rec) == 0;
}
