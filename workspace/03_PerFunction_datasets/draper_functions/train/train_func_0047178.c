init_client_compress(CONNECTION * con, unsigned int level)
{
    int n;

    ASSERT(validate_connection(con));
    ASSERT(ISUSER(con));
    con->uopt->zin = CALLOC(1, sizeof(z_stream));
    if(!con->uopt->zin)
    {
        OUTOFMEMORY("init_client_compress");
        return -1;
    }
    con->uopt->zout = CALLOC(1, sizeof(z_stream));
    if(!con->uopt->zout)
    {
        FREE(con->uopt->zin);
        OUTOFMEMORY("init_client_compress");
        return -1;
    }
    n = inflateInit(con->uopt->zin);
    if(n != Z_OK)
    {
        log_message_level(LOG_LEVEL_ERROR, "init_client_compress: inflateInit: %s (%d)", NONULL(con->uopt->zin->msg), n);
        return -1;
    }
    n = deflateInit(con->uopt->zout, level);
    if(n != Z_OK)
    {
        log_message_level(LOG_LEVEL_ERROR, "init_client_compress: deflateInit: %s (%d)", NONULL(con->uopt->zout->msg), n);
        return -1;
    }
    log_message_level(LOG_LEVEL_LOGIN, "init_client_compress: compressing client stream at level %d", level);
    stats.zusers++;
    return 0;
}
