gp_prepare_push_region_sep (void)
{
	GelETree *e1, *e2;

	e2 = gel_stack_pop (&gel_parsestack);
	e1 = gel_stack_pop (&gel_parsestack);

	if (e2->type == GEL_OPERATOR_NODE &&
	    e2->op.oper == GEL_E_REGION_SEP) {
		GelETree *a1 = e2->op.args;
		GelETree *a2 = e2->op.args->any.next;
		a1->any.next = NULL;
		a2->any.next = NULL;
		e2->op.args = NULL;
		gel_freetree (e2);
		gel_stack_push (&gel_parsestack, e1);
		gel_stack_push (&gel_parsestack, a1);
		gel_stack_push (&gel_parsestack, a2);

		return TRUE;
	} else {
		gel_stack_push (&gel_parsestack, e1);
		gel_stack_push (&gel_parsestack, e2);

		return FALSE;
	}
}
