finalize_client_compress(USEROPT * usr)
{
    int     n;

    n = deflateEnd(usr->zout);
    if(n != Z_OK)
        log_message_level(LOG_LEVEL_ERROR, "finalize_client_compress: deflateEnd: %s (%d)", NONULL(usr->zout->msg), n);
    n = inflateEnd(usr->zin);
    if(n != Z_OK)
        log_message_level(LOG_LEVEL_ERROR, "finalize_client_compress: inflateEnd: %s (%d)", NONULL(usr->zin->msg), n);
    FREE(usr->zin);
    FREE(usr->zout);

    stats.zusers--;
}
