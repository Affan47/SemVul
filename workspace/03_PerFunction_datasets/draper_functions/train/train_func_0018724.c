script_kill(const char *params) {
    int i;


    i = script_by_name(params);
    if (i < 0 || i >= num_scripts) {
        draw_ext_info(NDI_BLACK, MSG_TYPE_CLIENT, MSG_TYPE_CLIENT_SCRIPT,
            "No such running script");
        return;
    }
#ifndef WIN32
    kill(scripts[i].pid, SIGHUP);
#else
    GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, scripts[i].pid);
#endif
    draw_ext_info(NDI_RED, MSG_TYPE_CLIENT, MSG_TYPE_CLIENT_SCRIPT,
        "Killed script.");
    script_dead(i);
}
