dbd_st_rows(SV *h, imp_sth_t *imp_sth)
{
    dTHX;
    PERL_UNUSED_VAR(h);
    DBIh_SET_ERR_CHAR(h, imp_sth, 0, 1, "err msg", "12345", Nullch);
    return -1;
}
