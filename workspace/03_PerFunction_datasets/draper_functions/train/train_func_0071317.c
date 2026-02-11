enforce_quota(CHUNK_LIST& chunks) {
    if (!g_request->host.d_boinc_max) return 0;

    double x = g_request->host.d_boinc_used_project;
    if (config.debug_vda) {
        log_messages.printf(MSG_NORMAL,
            "[vda] share: %f used: %f\n",
            g_request->host.d_boinc_max, x
        );
    }
    CHUNK_LIST::iterator it = chunks.begin();
    while (x > g_request->host.d_boinc_max && it != chunks.end()) {
        DB_VDA_CHUNK_HOST& ch = it->second;
        if (!ch.found) continue;
        FILE_INFO fi;
        safe_strcpy(fi.name, ch.physical_file_name);
        if (config.debug_vda) {
            log_messages.printf(MSG_NORMAL,
                "[vda] deleting: %s\n", ch.physical_file_name
            );
        }
        DB_VDA_FILE vf;
        vf.lookup_id(ch.vda_file_id);
        x -= vf.chunk_size;
        g_reply->file_deletes.push_back(fi);
        it++;
    }
    return 0;
}
