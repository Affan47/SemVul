handle_reply(int http_op_retval) {
    bool error = false;
    if (http_op_retval) {
        error_num = http_op_retval;
        error = true;
    } else {
        string s;
        read_file_string(ALL_PROJECTS_LIST_FILENAME_TEMP, s);
        if (strstr(s.c_str(), "</projects>")) {
            boinc_rename(
                ALL_PROJECTS_LIST_FILENAME_TEMP, ALL_PROJECTS_LIST_FILENAME
            );
            gstate.all_projects_list_check_time = gstate.now;
        } else {
            error = true;
        }
    }


    if (error) {
        gstate.all_projects_list_check_time =
            gstate.now - ALL_PROJECTS_LIST_CHECK_PERIOD + SECONDS_PER_DAY;
    }
}
