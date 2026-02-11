constant()
    const
{
    if (!a1->constant())
	return false;
    rpt_value::pointer v1 = a1->evaluate_constant();
    if (v1->is_an_error())
    {
	return false;
    }
    rpt_value::pointer v1b = rpt_value::booleanize(v1);
    rpt_value_boolean *v1bp = dynamic_cast<rpt_value_boolean *>(v1b.get());
    if (!v1bp)
    {
	return false;
    }
    bool which = v1bp->query();

    return (which ? a2 : a3)->constant();
}
