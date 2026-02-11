DXLRemoveValueHandler(DXLConnection *conn, const char *name)
{
    if (!conn->valueHandlerDict)
	return OK;

    if (DictFind(conn->valueHandlerDict,name)) {
	DictDelete(conn->valueHandlerDict,name);
 	return OK;
    }

    return ERROR;
}
