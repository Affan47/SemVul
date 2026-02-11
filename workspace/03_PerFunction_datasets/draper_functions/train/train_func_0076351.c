label_inside_case(pval *label)
{
	pval *p = label;

	while( p && p->type != PV_MACRO && p->type != PV_CONTEXT )  {
		if( p->type == PV_CASE || p->type == PV_DEFAULT || p->type == PV_PATTERN ) {
			return 1;
		}

		p = p->dad;
	}
	return 0;
}
