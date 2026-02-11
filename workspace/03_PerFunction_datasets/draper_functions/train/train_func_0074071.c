cover_statement(pTHX_ OP *op)
{
    dMY_CXT;

    char *ch;
    SV  **count;
    IV    c;

    if (!collecting(Statement)) return;

    ch    = get_key(op);
    count = hv_fetch(MY_CXT.statements, ch, KEY_SZ, 1);
    c     = SvTRUE(*count) ? SvIV(*count) + 1 : 1;

    NDEB(D(L, "Statement: %s:%ld\n", CopFILE(cCOPx(op)), CopLINE(cCOPx(op))));

    sv_setiv(*count, c);
    NDEB(op_dump(op));
}
