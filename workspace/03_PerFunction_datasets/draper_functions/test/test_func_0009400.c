initialize_result(DB_RESULT& result, WORKUNIT& wu) {
    result.id = 0;
    result.create_time = time(0);
    result.workunitid = wu.id;
    result.size_class = wu.size_class;
    if (result.size_class < 0) {
        result.server_state = RESULT_SERVER_STATE_UNSENT;
    } else {
        result.server_state = RESULT_SERVER_STATE_INACTIVE;
    }
    result.hostid = 0;
    result.report_deadline = 0;
    result.sent_time = 0;
    result.received_time = 0;
    result.client_state = 0;
    result.cpu_time = 0;
    strcpy(result.xml_doc_out, "");
    strcpy(result.stderr_out, "");
    result.outcome = RESULT_OUTCOME_INIT;
    result.file_delete_state = ASSIMILATE_INIT;
    result.validate_state = VALIDATE_STATE_INIT;
    result.claimed_credit = 0;
    result.granted_credit = 0;
    result.appid = wu.appid;
    result.priority = wu.priority;
    result.batch = wu.batch;
}
