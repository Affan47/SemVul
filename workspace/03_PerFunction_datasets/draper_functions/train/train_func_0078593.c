mSyslog_close(VALUE self)
{
    rb_secure(4);
    if (!syslog_opened) {
        rb_raise(rb_eRuntimeError, "syslog not opened");
    }

    closelog();

    free((void *)syslog_ident);
    syslog_ident = NULL;
    syslog_options = syslog_facility = syslog_mask = -1;
    syslog_opened = 0;

    return Qnil;
}
