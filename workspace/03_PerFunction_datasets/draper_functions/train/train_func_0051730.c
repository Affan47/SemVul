show_message(
    PROJ_AM *p, char* msg, int priority, bool is_html, const char* link
) {
    const char* x;
    char message[1024], event_msg[1024];
    char* time_string = time_to_string(gstate.now);


    diagnostics_cycle_logs();

    strlcpy(message, msg, sizeof(message));


    while (strlen(message) && message[strlen(message)-1] == '\n') {
        message[strlen(message)-1] = 0;
    }


    switch (priority) {
    case MSG_INTERNAL_ERROR:
        snprintf(event_msg, sizeof(event_msg), "[error] %s", message);
        break;
    case MSG_SCHEDULER_ALERT:
        snprintf(event_msg, sizeof(event_msg), "%s: %s",
            _("Message from server"), message
        );
        break;
    default:
        strlcpy(event_msg, message, sizeof(event_msg));
    }
    message_descs.insert(p, priority, (int)gstate.now, event_msg);


    switch (priority) {
    case MSG_USER_ALERT:
    case MSG_SCHEDULER_ALERT:
        char buf[1024];
        if (is_html) {
            xml_escape(message, buf, 1024);
        } else {
            char buf2[1024];
            xml_escape(message, buf2, 1024);
            xml_escape(buf2, buf, 1024);
        }
        NOTICE n;
        n.description = buf;
        if (link) {
            safe_strcpy(n.link, link);
        }
        if (p) {
            safe_strcpy(n.project_name, p->get_project_name());
        }
        n.create_time = n.arrival_time = gstate.now;
        safe_strcpy(n.category, (priority==MSG_USER_ALERT)?"client":"scheduler");
        notices.append(n);
    }

    strip_translation(message);

    if (p) {
        x = p->get_project_name();
    } else {
        x = "---";
    }
    printf("%s [%s] %s\n", time_string, x, message);

#if defined(_WIN32) || defined(ANDROID)
    char evt_message[2048];
    snprintf(evt_message, sizeof(evt_message), "%s [%s] %s\n", time_string,  x, message);

#ifdef _WIN32
    ::OutputDebugString(evt_message);
#endif

#endif

}
