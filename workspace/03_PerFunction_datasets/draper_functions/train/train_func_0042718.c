finalize_compress(SERVER * serv)
{
    int     n;

    n = deflateEnd(serv->zout);
    if(n != Z_OK)
        log_message_level(LOG_LEVEL_ERROR,"finalize_compress: deflateEnd: %s (%d)",  NONULL(serv->zout->msg), n);
    n = inflateEnd(serv->zin);
    if(n != Z_OK)
        log_message_level(LOG_LEVEL_ERROR, "finalize_compress: inflateEnd: %s (%d)", NONULL(serv->zin->msg), n);
    FREE(serv->zin);
    FREE(serv->zout);
}
