strscan_rest_size(VALUE self)
{
    struct strscanner *p;
    long i;

    GET_SCANNER(self, p);
    if (EOS_P(p)) {
        return INT2FIX(0);
    }
    i = S_LEN(p) - p->curr;
    return INT2FIX(i);
}
