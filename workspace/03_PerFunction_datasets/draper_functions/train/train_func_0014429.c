range_first(int argc, VALUE *argv, VALUE range)
{
    VALUE n, ary[2];

    if (argc == 0) return RANGE_BEG(range);

    rb_scan_args(argc, argv, "1", &n);
    ary[0] = n;
    ary[1] = rb_ary_new2(NUM2LONG(n));
    rb_block_call(range, rb_intern("each"), 0, 0, first_i, (VALUE)ary);

    return ary[1];
}
