init_result(RESULT& result, void*& data) {
    int retval;
    FILE_CKSUM_LIST* fcl = new FILE_CKSUM_LIST;
    vector<OUTPUT_FILE_INFO> files;
    char md5_buf[MD5_LEN];
    double nbytes;

    retval = get_output_file_infos(result, files);
    if (retval) {
        log_messages.printf(MSG_CRITICAL,
            "[RESULT#%u %s] check_set: can't get output filenames\n",
            result.id, result.name
        );
        return retval;
    }

    for (unsigned int i=0; i<files.size(); i++) {
        OUTPUT_FILE_INFO& fi = files[i];
        if (fi.no_validate) continue;
        retval = md5_file(fi.path.c_str(), md5_buf, nbytes);
        if (retval) {
            if (fi.optional) {
                strcpy(md5_buf, "");

            } else {
                log_messages.printf(MSG_CRITICAL,
                    "[RESULT#%u %s] Couldn't open %s\n",
                    result.id, result.name, fi.path.c_str()
                );
                return retval;
            }
        }
        fcl->files.push_back(string(md5_buf));
    }
    data = (void*) fcl;
    return 0;
}
