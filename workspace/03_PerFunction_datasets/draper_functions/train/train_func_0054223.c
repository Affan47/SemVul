strscan_matched_size(VALUE self)
{
    struct strscanner *p;

    GET_SCANNER(self, p);
    if (! MATCHED_P(p)) return Qnil;
    return INT2NUM(p->regs.end[0] - p->regs.beg[0]);
}
