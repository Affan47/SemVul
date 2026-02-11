fl_isnumber(value_t v)
{
    if (isfixnum(v)) return 1;
    if (iscprim(v)) {
        cprim_t *c = (cprim_t*)ptr(v);
        return c->type != wchartype;
    }
    return 0;
}
