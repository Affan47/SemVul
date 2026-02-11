SQLiteUpdateCommand(const char *str)
{
    char *zErrMsg;
    int ret = sqlite3_exec(connection, str, NULL, NULL, &zErrMsg);
    if (ret != SQLITE_OK) {
        outputerrf("SQL error: %s\nfrom '%s'", zErrMsg, str);
        sqlite3_free(zErrMsg);
    }
    return (ret == SQLITE_OK);
}
