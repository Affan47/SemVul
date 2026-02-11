s_log(int level, const char *format, ...) {
    va_list ap;
    char *text, *stamp, *id;
    unsigned long tid;
    struct LIST *tmp;
    int libc_error, socket_error;
    time_t gmt;
    struct tm *timeptr;
#if defined(HAVE_LOCALTIME_R) && defined(_REENTRANT)
    struct tm timestruct;
#endif


    if(mode==LOG_MODE_CONFIGURED && level>global_options.debug_level)
        return;

    libc_error=get_last_error();
    socket_error=get_last_socket_error();

    time(&gmt);
#if defined(HAVE_LOCALTIME_R) && defined(_REENTRANT)
    timeptr=localtime_r(&gmt, &timestruct);
#else
    timeptr=localtime(&gmt);
#endif
    stamp=str_printf("%04d.%02d.%02d %02d:%02d:%02d",
        timeptr->tm_year+1900, timeptr->tm_mon+1, timeptr->tm_mday,
        timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);
    tid=stunnel_thread_id();
    if(!tid)
        tid=stunnel_process_id();
    id=str_printf("LOG%d[%lu]", level, tid);
    va_start(ap, format);
    text=str_vprintf(format, ap);
    va_end(ap);

    if(mode==LOG_MODE_NONE) {
        enter_critical_section(CRIT_LOG);
        tmp=str_alloc(sizeof(struct LIST));
        str_detach(tmp);
        tmp->next=NULL;
        tmp->level=level;
        tmp->stamp=stamp;
        str_detach(tmp->stamp);
        tmp->id=id;
        str_detach(tmp->id);
        tmp->text=text;
        str_detach(tmp->text);
        if(tail)
            tail->next=tmp;
        else
            head=tmp;
        tail=tmp;
        leave_critical_section(CRIT_LOG);
    } else {
        log_raw(level, stamp, id, text);
        str_free(stamp);
        str_free(id);
        str_free(text);
    }

    set_last_error(libc_error);
    set_last_socket_error(socket_error);
}
