_get_log_id()
{
    int i;
    int id = -1;


    _lock_logger();

    for (i = 0; i < LOG_MAXLOGS; i++)
        if (loglist[i].in_use == 0) {
            loglist[i].in_use = 1;
            id = i;
            break;
        }


    _unlock_logger();

    return id;
}
