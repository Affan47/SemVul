evaluate(string_ty *path_unres, string_ty *path,
    string_ty *path_res, struct stat *st) const
{
    rpt_value::pointer vp = get_arg()->evaluate(path_unres, path, path_res, st);
    if (vp->is_an_error())
        return vp;
    rpt_value::pointer svp = rpt_value::stringize(vp);
    rpt_value_string *svpp = dynamic_cast<rpt_value_string *>(svp.get());
    if (!svpp)
    {
        sub_context_ty sc;
        sc.var_set_charstar("Function", "atime");
        sc.var_set_long("Number", 1);
        sc.var_set_charstar("Name", vp->name());
        nstring s
        (
            sc.subst_intl
            (
                i18n("$function: argument $number: string value required (was "
                    "given $name)")
            )
        );
        return rpt_value_error::create(s);
    }

    nstring s = svpp->query();
    if (nstring(path_unres) == s || nstring(path_res) == s)
        return rpt_value_time::create(st->st_atime);

    string_ty *fn = stack_relative(s.get_ref());
    struct stat st2;
    string_ty *resolved_fn = stat_stack(fn, &st2);
    rpt_value::pointer result = rpt_value_time::create(st2.st_atime);
    str_free(fn);
    str_free(resolved_fn);
    return result;
}
