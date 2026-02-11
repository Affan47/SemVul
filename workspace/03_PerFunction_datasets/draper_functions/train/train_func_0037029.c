mSyslog_facility(VALUE self)
{
    return syslog_opened ? INT2NUM(syslog_facility) : Qnil;
}
