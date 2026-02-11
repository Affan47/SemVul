run(rpt_stmt_result_ty *rp)
    const
{


    trace(("foreach::run()\n{\n"));
    rpt_value::pointer lhs = e[0]->evaluate(true, false);
    if (lhs->is_an_error())
    {
       	rp->status = rpt_stmt_status_error;
       	rp->thrown = lhs;
       	trace(("}\n"));
       	return;
    }
    rpt_value_reference *lhs_ref_p =
        dynamic_cast<rpt_value_reference *>(lhs.get());
    if (!lhs_ref_p)
    {
       	sub_context_ty sc;
       	sc.var_set_charstar("Name", lhs->name());
       	nstring s
        (
	    sc.subst_intl
	    (
	       	i18n("the loop variable must be modifiable (not $name)")
	    )
        );
       	rp->status = rpt_stmt_status_error;
       	rp->thrown = rpt_value_error::create(e[0]->get_pos(), s);
       	trace(("}\n"));
       	return;
    }

    rpt_value::pointer rhs = e[1]->evaluate(true, true);
    if (rhs->is_an_error())
    {
       	rp->status = rpt_stmt_status_error;
       	rp->thrown = rhs;
       	trace(("}\n"));
       	return;
    }
    rpt_value_null *rhs_null_p = dynamic_cast<rpt_value_null *>(rhs.get());
    if (rhs_null_p)
    {


       	trace(("loop list nul\n"));
       	rp->status = rpt_stmt_status_normal;
       	rp->thrown.reset();
       	trace(("}\n"));
       	return;
    }
    rpt_value_list *rhs_list_p = dynamic_cast<rpt_value_list *>(rhs.get());
    if (!rhs_list_p)
    {
       	sub_context_ty sc;
       	sc.var_set_charstar("Name", rhs->name());
       	nstring s
        (
	    sc.subst_intl
	    (
	       	i18n("the loop iteration value must be a list (not $name)")
	    )
        );
       	rp->status = rpt_stmt_status_error;
       	rp->thrown = rpt_value_error::create(e[1]->get_pos(), s);
       	trace(("}\n"));
       	return;
    }


    size_t rhs_length = rhs_list_p->size();
    for (size_t j = 0; j < rhs_length; ++j)
    {


       	trace(("loop index %ld;\n", (long)j));
        rpt_value::pointer vp = rhs_list_p->nth(j);
       	lhs_ref_p->set(vp);


       	nth_child(0)->run(rp);
       	switch (rp->status)
       	{
       	case rpt_stmt_status_error:
       	case rpt_stmt_status_return:


	    trace(("loop exit\n"));
	    trace(("}\n"));
	    return;

       	case rpt_stmt_status_normal:
       	case rpt_stmt_status_continue:


	    trace(("loop normal\n"));
	    continue;

       	case rpt_stmt_status_break:


	    trace(("loop break\n"));
	    break;
       	}
       	break;
    }
    trace(("loop complete\n"));
    rp->status = rpt_stmt_status_normal;
    rp->thrown.reset();
    trace(("}\n"));
}
