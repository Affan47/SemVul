run(const rpt_expr::pointer &, size_t,
    rpt_value::pointer *argv) const
{
    rpt_value::pointer arg = rpt_value::undefer(argv[0]);
    return rpt_value_string::create(arg->type_of());
}
