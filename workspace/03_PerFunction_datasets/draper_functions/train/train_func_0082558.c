parse_mday_cb(VALUE m, VALUE hash)
{
    VALUE d;

    d = rb_reg_nth_match(1, m);
    set_hash("mday", str2num(d));
    return 1;
}
