strftimev(const char *fmt, VALUE time)
{
    struct time_object *tobj;
    char buffer[SMALLBUF], *buf = buffer;
    long len;
    VALUE str;

    GetTimeval(time, tobj);
    MAKE_TM(time, tobj);
    len = rb_strftime_alloc(&buf, fmt, &tobj->vtm, tobj->timew, TIME_UTC_P(tobj));
    str = rb_str_new(buf, len);
    if (buf != buffer) xfree(buf);
    return str;
}
