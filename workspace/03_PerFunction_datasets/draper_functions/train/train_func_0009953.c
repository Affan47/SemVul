handle_vda() {
    int retval;
    unsigned int i;
    CHUNK_LIST chunks;


    if (outdated_client(g_reply->host)) {
        g_reply->host.cpu_efficiency = 1;
        return;
    }


    g_reply->host.cpu_efficiency = 0;


    DB_VDA_CHUNK_HOST ch;
    char buf[256];
    sprintf(buf, "where host_id=%d", g_reply->host.id);
    while (1) {
        retval = ch.enumerate(buf);
        if (retval == ERR_DB_NOT_FOUND) break;
        if (retval) {


            log_messages.printf(MSG_NORMAL,
                "[vda]: ch.enumerate() failed %d\n", retval
            );
            return;
        }
        if (config.debug_vda) {
            log_messages.printf(MSG_NORMAL,
                "[vda] DB: has chunk %s, file %d\n",
                ch.physical_file_name, ch.vda_file_id
            );
        }
        chunks.insert(
            pair<string, DB_VDA_CHUNK_HOST>(string(ch.physical_file_name), ch)
        );
    }


    for (i=0; i<g_request->file_xfer_results.size(); i++) {
        RESULT& r = g_request->file_xfer_results[i];
        if (strstr(r.name, "upload_vda_")) {
            char* phys_file_name = r.name + strlen("upload_");
            if (config.debug_vda) {
                log_messages.printf(MSG_NORMAL,
                    "[vda] completed upload of %s\n", phys_file_name
                );
            }
            retval = process_completed_upload(phys_file_name, chunks);
            if (retval) {
                log_messages.printf(MSG_CRITICAL,
                    "[vda] process_completed_upload(): %d\n", retval
                );
                return;
            }
        }
    }


    for (i=0; i<g_request->file_infos.size(); i++) {
        FILE_INFO& fi = g_request->file_infos[i];
        if (!starts_with(fi.name, "vda_")) {
            continue;
        }
        if (config.debug_vda) {
            log_messages.printf(MSG_NORMAL,
                "[vda] request: client has file %s, status %d\n",
                fi.name, fi.status
            );
        }
        if (fi.status != FILE_PRESENT) {
            continue;
        }
        process_chunk_present_on_client(fi, chunks);
    }

    process_chunks_missing_on_client(chunks);

    enforce_quota(chunks);

    issue_transfer_commands(chunks);
}
