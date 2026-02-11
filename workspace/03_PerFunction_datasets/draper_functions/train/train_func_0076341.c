time_usec(VALUE time)
{
    struct time_object *tobj;
    wideval_t w, q, r;

    GetTimeval(time, tobj);

    w = wmod(tobj->timew, WINT2WV(TIME_SCALE));
    wmuldivmod(w, WINT2FIXWV(1000000), WINT2FIXWV(TIME_SCALE), &q, &r);
    return rb_to_int(w2v(q));
}
