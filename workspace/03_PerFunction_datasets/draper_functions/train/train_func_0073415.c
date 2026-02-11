issue_transfer_commands(CHUNK_LIST& chunks) {
    char xml_buf[8192], chunk_name[256], file_name[1024];
    int retval;
    char url[1024], buf[1024];

    CHUNK_LIST::iterator it;
    for (it = chunks.begin(); it != chunks.end(); it++) {
        vector<const char*> urls;
        DB_VDA_CHUNK_HOST& ch = it->second;
        if (!ch.transfer_in_progress) continue;
        if (!ch.transfer_wait) continue;
        DB_VDA_FILE vf;
        retval = vf.lookup_id(ch.vda_file_id);
        if (retval) return retval;
        if (ch.present_on_host) {


            sprintf(buf, "upload_%s", ch.physical_file_name);
            if (result_already_on_host(buf)) {
                if (config.debug_vda) {
                    log_messages.printf(MSG_NORMAL,
                        "[vda] upload of %s already in progress\n",
                        ch.physical_file_name
                    );
                }
                continue;
            }
            if (config.debug_vda) {
                log_messages.printf(MSG_NORMAL,
                    "[vda] sending command to upload %s\n",
                    ch.physical_file_name
                );
            }
            urls.push_back(config.upload_url);
            R_RSA_PRIVATE_KEY key;
            retval = get_file_xml(
                ch.physical_file_name,
                urls,
                vf.chunk_size,
                dtime() + VDA_HOST_TIMEOUT,
                false,
                key,
                xml_buf
            );
        } else {


            sprintf(buf, "download_%s", ch.physical_file_name);
            if (result_already_on_host(buf)) {
                if (config.debug_vda) {
                    log_messages.printf(MSG_NORMAL,
                        "[vda] download of %s already in progress\n",
                        ch.physical_file_name
                    );
                }
                continue;
            }
            char md5[64], chunk_dir[1024];
            int hostid;
            if (config.debug_vda) {
                log_messages.printf(MSG_NORMAL,
                    "[vda] sending command to download %s\n",
                    ch.physical_file_name
                );
            }
            parse_physical_filename(
                ch.physical_file_name,
                hostid,
                chunk_name, sizeof(chunk_name),
                file_name, sizeof(file_name)
            );

            get_chunk_url(vf, chunk_name, url);
            urls.push_back(url);
            get_chunk_dir(vf, chunk_name, chunk_dir);
            retval = get_chunk_md5(chunk_dir, md5);
            if (retval) return retval;
            retval = put_file_xml(
                ch.physical_file_name,
                urls,
                md5,
                vf.chunk_size,
                dtime() + VDA_HOST_TIMEOUT,
                xml_buf
            );
        }
        g_reply->file_transfer_requests.push_back(string(xml_buf));
    }
    return 0;
}
