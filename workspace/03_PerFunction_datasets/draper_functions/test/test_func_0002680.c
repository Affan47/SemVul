time_s_at(int argc, VALUE *argv, VALUE klass)
{
    VALUE time, t;
    wideval_t timew;

    if (rb_scan_args(argc, argv, "11", &time, &t) == 2) {
        time = num_exact(time);
        t = num_exact(t);
        timew = wadd(rb_time_magnify(v2w(time)), wmulquoll(v2w(t), TIME_SCALE, 1000000));
        t = time_new_timew(klass, timew);
    }
    else if (IsTimeval(time)) {
	struct time_object *tobj, *tobj2;
        GetTimeval(time, tobj);
        t = time_new_timew(klass, tobj->timew);
	GetTimeval(t, tobj2);
        TIME_COPY_GMT(tobj2, tobj);
    }
    else {
        timew = rb_time_magnify(v2w(num_exact(time)));
        t = time_new_timew(klass, timew);
    }

    return t;
}
