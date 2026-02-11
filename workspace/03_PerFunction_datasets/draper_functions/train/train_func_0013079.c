sharedsv_elem_mg_dup(pTHX_ MAGIC *mg, CLONE_PARAMS *param)
{
    PERL_UNUSED_ARG(param);
    SvREFCNT_inc_void(SHAREDSV_FROM_OBJ(mg->mg_obj));
    assert(mg->mg_flags & MGf_DUP);
    return (0);
}
