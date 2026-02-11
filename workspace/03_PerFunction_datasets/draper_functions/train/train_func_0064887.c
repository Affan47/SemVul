open_archive(const char* filename_prefix, FILE*& f){
    char path[MAXPATHLEN];
    char command[MAXPATHLEN+512];

    if (daily_dir) {
        time_t time_time = time_int;
        char dirname[32];
        strftime(dirname, sizeof(dirname), "%Y_%m_%d", gmtime(&time_time));
        safe_strcpy(path, config.project_path("archives/%s",dirname));
        if (mkdir(path,0775)) {
            if(errno!=EEXIST) {
                char errstr[256];
                sprintf(errstr, "could not create directory '%s': %s\n",
                path, strerror(errno));
                fail(errstr);
            }
        }
        safe_strcpy(path,
            config.project_path(
                "archives/%s/%s_%d.xml", dirname, filename_prefix, time_int
            )
        );
    } else {
        safe_strcpy(path,
            config.project_path("archives/%s_%d.xml", filename_prefix, time_int)
        );
    }

    strcat(path, suffix[compression_type]);


    if (compression_type == COMPRESSION_GZIP) {
        sprintf(command, "gzip - > %s", path);
    }

    if (compression_type == COMPRESSION_ZIP) {
        sprintf(command, "zip - - > %s", path);
    }

    log_messages.printf(MSG_NORMAL,
        "Opening archive %s\n", path
    );

    if (compression_type == COMPRESSION_NONE) {
        if (!(f = fopen(path,"w"))) {
            char buf[256];
            sprintf(buf, "Can't open archive file %s %s\n",
                path, errno?strerror(errno):""
            );
            fail(buf);
        }
    } else {
        f = popen(command,"w");
        if (!f) {
            log_messages.printf(MSG_CRITICAL,
                "Can't open pipe %s %s\n",
                command, errno?strerror(errno):""
            );
            exit(4);
        }
    }


    setlinebuf(f);

    return;
}
