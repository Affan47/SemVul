time_fixoff(VALUE time)
{
    struct time_object *tobj;
    struct vtm vtm;
    VALUE off;

    GetTimeval(time, tobj);
    if (TIME_FIXOFF_P(tobj)) {
       if (tobj->tm_got)
           return time;
    }
    else {
       time_modify(time);
    }

    if (TIME_FIXOFF_P(tobj))
        off = tobj->vtm.utc_offset;
    else
        off = INT2FIX(0);

    if (!gmtimew(tobj->timew, &vtm))
       rb_raise(rb_eArgError, "gmtime error");

    tobj->vtm = vtm;
    vtm_add_offset(&tobj->vtm, off);

    tobj->tm_got = 1;
    TIME_SET_FIXOFF(tobj, off);
    return time;
}
