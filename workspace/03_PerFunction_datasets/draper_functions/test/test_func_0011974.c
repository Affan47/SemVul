evaluate()
    const
{
    trace(("%s\n", __PRETTY_FUNCTION__));
    assert(get_nchildren() == 2);
    rpt_value::pointer v1 = nth_child(0)->evaluate(true, true);
    trace(("v1 is %s\n", v1->name()));
    if (v1->is_an_error())
	return v1;
    rpt_value::pointer v1i = rpt_value::integerize(v1);
    trace(("v1i is %s\n", v1i->name()));
    rpt_value_integer *v1ip = dynamic_cast<rpt_value_integer *>(v1i.get());
    if (!v1ip)
    {
	sub_context_ty sc;
	sc.var_set_charstar("Name", v1->name());
	nstring s
        (
	    sc.subst_intl
	    (
		i18n("integer value required for bit and (was given $name)")
	    )
        );
	assert(nth_child(0)->get_pos());
	rpt_value::pointer result =
            rpt_value_error::create(nth_child(0)->get_pos(), s);
	return result;
    }
    trace(("v1ip is %ld\n", v1ip->query()));

    rpt_value::pointer v2 = nth_child(1)->evaluate(true, true);
    trace(("v2 is %s\n", v2->name()));
    if (v2->is_an_error())
	return v2;
    rpt_value::pointer v2i = rpt_value::integerize(v2);
    trace(("v2i is %s\n", v2i->name()));
    rpt_value_integer *v2ip = dynamic_cast<rpt_value_integer *>(v2i.get());
    if (!v2ip)
    {
	sub_context_ty sc;
	sc.var_set_charstar("Name", v2->name());
	nstring s
        (
	    sc.subst_intl
	    (
		i18n("integer value required for bit and (was given $name)")
	    )
        );
        rpt_value::pointer result =
            rpt_value_error::create(nth_child(1)->get_pos(), s);
	return result;
    }
    trace(("v2ip is %ld\n", v2ip->query()));

    return rpt_value_integer::create(v1ip->query() & v2ip->query());
}
