inject_i(i, memo)
    VALUE i;
    VALUE *memo;
{
    if (*memo == Qundef) {
        *memo = i;
    }
    else {
        *memo = rb_yield_values(2, *memo, i);
    }
    return Qnil;
}
