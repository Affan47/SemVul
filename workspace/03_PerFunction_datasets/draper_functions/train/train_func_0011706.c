uiDXLOpenImageByTitle(DXLConnection *conn, char *title)
{
    char buf[1024];
    sprintf(buf, "open image title=%s", title);
    if (!conn->dxuiConnected)
        return ERROR;
    return DXLSend(conn, buf);
}
