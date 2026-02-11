add_job_files_to_host(WORKUNIT& wu) {
    MIOFILE mf;
    mf.init_buf_read(wu.xml_doc);
    XML_PARSER xp(&mf);
    while (!xp.get_tag()) {
        if (xp.match_tag("file_info")) {
            FILE_INFO fi;
            int retval = fi.parse(xp);
            if (retval) continue;
            if (!fi.sticky) continue;
            if (!file_present_on_host(fi.name)) {
                if (config.debug_send) {
                    log_messages.printf(MSG_NORMAL,
                        "[send] Adding file %s to host file list\n", fi.name
                    );
                }
                g_request->file_infos.push_back(fi);
            }
        }
    }
}
