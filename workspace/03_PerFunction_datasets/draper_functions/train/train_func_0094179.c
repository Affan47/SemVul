wquo(wideval_t wx, wideval_t wy)
{
    VALUE x, y, ret;
#if WIDEVALUE_IS_WIDER
    if (FIXWV_P(wx) && FIXWV_P(wy)) {
        wideint_t a, b, c;
        a = FIXWV2WINT(wx);
        b = FIXWV2WINT(wy);
        if (b == 0) rb_num_zerodiv();
        c = a / b;
        if (c * b == a) {
            return WINT2WV(c);
        }
    }
#endif
    x = w2v(wx);
    y = w2v(wy);
    ret = rb_funcall(x, id_quo, 1, y);
    if (TYPE(ret) == T_RATIONAL &&
        RRATIONAL(ret)->den == INT2FIX(1)) {
        ret = RRATIONAL(ret)->num;
    }
    return v2w(ret);
}
