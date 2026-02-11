time_add(tobj, offset, sign)
    struct time_object *tobj;
    VALUE offset;
    int sign;
{
    double v = NUM2DBL(offset);
    double f, d;
    unsigned_time_t sec_off;
    time_t usec_off, sec, usec;
    VALUE result;

    if (v < 0) {
        v = -v;
        sign = -sign;
    }
    d = modf(v, &f);
    sec_off = (unsigned_time_t)f;
    if (f != (double)sec_off)
        rb_raise(rb_eRangeError, "time %s %f out of Time range",
            sign < 0 ? "-" : "+", v);
    usec_off = (time_t)(d*1e6);

    if (sign < 0) {
        sec = tobj->tv.tv_sec - sec_off;
        usec = tobj->tv.tv_usec - usec_off;
        if (sec > tobj->tv.tv_sec)
            rb_raise(rb_eRangeError, "time - %f out of Time range", v);
    }
    else {
        sec = tobj->tv.tv_sec + sec_off;
        usec = tobj->tv.tv_usec + usec_off;
        if (sec < tobj->tv.tv_sec)
            rb_raise(rb_eRangeError, "time + %f out of Time range", v);
    }
    result = rb_time_new(sec, usec);
    if (tobj->gmt) {
	GetTimeval(result, tobj);
	tobj->gmt = 1;
    }
    return result;
}
