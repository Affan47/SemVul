httpMapFile(HttpConn *conn, HttpRoute *route)
{
    HttpRx      *rx;
    HttpTx      *tx;
    HttpLang    *lang;
    MprPath     *info;

    mprAssert(conn);
    mprAssert(route);

    rx = conn->rx;
    tx = conn->tx;
    lang = rx->lang;

    mprAssert(rx->target);
    tx->filename = rx->target;
    if (lang && lang->path) {
        tx->filename = mprJoinPath(lang->path, tx->filename);
    }
    tx->filename = mprJoinPath(route->dir, tx->filename);
    tx->ext = httpGetExt(conn);
    info = &tx->fileInfo;
    mprGetPathInfo(tx->filename, info);
    if (info->valid) {
        tx->etag = sfmt("\"%x-%Lx-%Lx\"", info->inode, info->size, info->mtime);
    }
    LOG(7, "mapFile uri \"%s\", filename: \"%s\", extension: \"%s\"", rx->uri, tx->filename, tx->ext);
}
