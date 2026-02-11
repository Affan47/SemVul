cmp_gt(VALUE x, VALUE y)
{
    VALUE c = rb_funcall(x, cmp, 1, y);

    if (rb_cmpint(c, x, y) > 0) return Qtrue;
    return Qfalse;
}
