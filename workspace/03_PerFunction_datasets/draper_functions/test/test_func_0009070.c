db__recv_handle(dbHandle * handle)
{
    DB_RECV_STRING(&handle->dbName);
    DB_RECV_STRING(&handle->dbSchema);

    return DB_OK;
}
