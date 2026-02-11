stmt_compound_append(stmt_ty *that, stmt_ty *lp)
{
    stmt_compound_ty *this;

    trace(("stmt_compound_append()\n{\n"));
    this = (stmt_compound_ty *)that;
    if (lp->method == &method)
    {
        stmt_compound_ty *lp2;


        trace(("mark\n"));
        lp2 = (stmt_compound_ty *)lp;
        append_n(this, lp2->line, lp2->nlines);
        lp2->nlines = 0;
        stmt_free(lp);
    }
    else
        append_n(this, &lp, (size_t) 1);
    trace(("}\n"));
}
