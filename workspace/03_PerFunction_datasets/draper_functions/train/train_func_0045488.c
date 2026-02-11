evaluate()
    const
{


    trace(("match::evaluate()\n"));
    assert(get_nchildren() == 2);
    rpt_value::pointer lv1 = nth_child(0)->evaluate(true, true);
    if (lv1->is_an_error())
        return lv1;


    rpt_value::pointer lv2 = rpt_value::stringize(lv1);


    rpt_value::pointer rv1 = nth_child(1)->evaluate(true, true);
    if (rv1->is_an_error())
        return rv1;


    rpt_value::pointer rv2 = rpt_value::stringize(rv1);


    rpt_value_string *lsp = dynamic_cast<rpt_value_string *>(lv2.get());
    rpt_value_string *rsp = dynamic_cast<rpt_value_string *>(rv2.get());
    if (lsp && rsp)
    {
        return
            rpt_value_real::create
            (
                fstrcmp(lsp->query().c_str(), rsp->query().c_str())
            );
    }

    sub_context_ty sc;
    sc.var_set_charstar("Name1", lv1->name());
    sc.var_set_charstar("Name2", rv1->name());
    nstring s(sc.subst_intl(i18n("illegal comparison ($name1 ~~ $name2)")));
    return rpt_value_error::create(get_pos(), s);
}
