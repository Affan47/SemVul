tgdb_process_info_sources(struct tgdb *tgdb, tgdb_request_ptr request)
{
    int ret;

    if (!tgdb || !request)
        return -1;

    if (request->header != TGDB_REQUEST_INFO_SOURCES)
        return -1;

    ret = tgdb_client_get_inferior_source_files(tgdb->tcc);
    tgdb_process_client_commands(tgdb);

    return ret;
}
