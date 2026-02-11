report_result_error(RESULT& res, const char* format, ...) {
    char buf[4096],  err_msg[4096];


    unsigned int i;
    int failnum;


    if (res.ready_to_report) {
        return 0;
    }

    res.set_ready_to_report();
    res.completed_time = now;

    va_list va;
    va_start(va, format);
    vsnprintf(err_msg, sizeof(err_msg), format, va);
    va_end(va);

    sprintf(buf, "Unrecoverable error for task %s", res.name);
#ifndef SIM
    scheduler_op->project_rpc_backoff(res.project, buf);
#endif

    sprintf( buf, "<message>\n%s\n</message>\n", err_msg);
    res.stderr_out.append(buf);

    switch(res.state()) {
    case RESULT_NEW:
    case RESULT_FILES_DOWNLOADING:


        if (!res.exit_status) {
            res.exit_status = ERR_RESULT_DOWNLOAD;
        }
        break;

    case RESULT_FILES_DOWNLOADED:


        res.set_state(RESULT_COMPUTE_ERROR, "CS::report_result_error");
        if (!res.exit_status) {
            res.exit_status = ERR_RESULT_START;
        }
        break;

    case RESULT_FILES_UPLOADING:


        for (i=0; i<res.output_files.size(); i++) {
            if (res.output_files[i].file_info->had_failure(failnum)) {
                sprintf(buf,
                    "<upload_error>\n"
                    "    <file_name>%s</file_name>\n"
                    "    <error_code>%d</error_code>\n"
                    "</upload_error>\n",
                    res.output_files[i].file_info->name, failnum
                );
                res.stderr_out.append(buf);
            }
        }
        if (!res.exit_status) {
            res.exit_status = ERR_RESULT_UPLOAD;
        }
        res.set_state(RESULT_UPLOAD_FAILED, "CS::report_result_error");
        break;
    case RESULT_FILES_UPLOADED:
        msg_printf(res.project, MSG_INTERNAL_ERROR,
            "Error reported for completed task %s", res.name
        );
        break;
    }

    res.stderr_out = res.stderr_out.substr(0, MAX_STDERR_LEN);
    return 0;
}
