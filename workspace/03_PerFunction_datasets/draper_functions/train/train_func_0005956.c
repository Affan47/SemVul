create(const rpt_expr::pointer &e0, const rpt_expr::pointer &e1,
    const rpt_expr::pointer &e2, const rpt_stmt::pointer &body)
{
    return pointer(new rpt_stmt_for(e0, e1, e2, body));
}
