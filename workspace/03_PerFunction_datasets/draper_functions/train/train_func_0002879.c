run(rpt_stmt_result_ty *rp)
    const
{


    rpt_value::pointer vp = e[0]->evaluate(true, true);
    if (vp->is_an_error())
    {
       	rp->status = rpt_stmt_status_error;
       	rp->thrown = vp;
       	return;
    }


    for (;;)
    {


       	vp = e[1]->evaluate(true, true);
       	if (vp->is_an_error())
       	{
	    rp->status = rpt_stmt_status_error;
	    rp->thrown = vp;
	    return;
       	}


	rpt_value::pointer vp2 = rpt_value::booleanize(vp);
        rpt_value_boolean *vp2bp = dynamic_cast<rpt_value_boolean *>(vp2.get());
	if (!vp2bp)
	{
	    sub_context_ty sc;
	    sc.var_set_charstar("Name", vp2->name());
	    nstring s
            (
	     	sc.subst_intl
	     	(
		    i18n("loop condition must be boolean (not $name)")
	     	)
            );
	    rp->status = rpt_stmt_status_error;
	    rp->thrown = rpt_value_error::create(e[1]->get_pos(), s);
	    return;
       	}


       	if (!vp2bp->query())
       	{
	    break;
       	}


	nth_child(0)->run(rp);
       	switch (rp->status)
       	{
       	case rpt_stmt_status_error:
       	case rpt_stmt_status_return:


	    trace(("loop exit\n"));
	    return;

       	case rpt_stmt_status_normal:
       	case rpt_stmt_status_continue:


	    trace(("loop normal\n"));
	    vp = e[2]->evaluate(true, true);
	    if (vp->is_an_error())
	    {
	     	rp->status = rpt_stmt_status_error;
	     	rp->thrown = vp;
	     	return;
	    }


	    continue;

       	case rpt_stmt_status_break:


	    trace(("loop break\n"));
	    break;
       	}
       	break;
    }
    rp->status = rpt_stmt_status_normal;
    rp->thrown.reset();
}
