test_op_linklist_describe(OP *start)
{
    SV *rv = sv_2mortal(newSVpvs(""));
    OP *o;
    o = start = LINKLIST(start);
    do {
        sv_catpvs(rv, ".");
        sv_catpv(rv, OP_NAME(o));
        if (o->op_type == OP_CONST)
            sv_catsv(rv, cSVOPo->op_sv);
        o = o->op_next;
    } while (o && o != start);
    return SvPVX(rv);
}
