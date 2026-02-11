eliminate_subexp_dosum_sum_statement(Module_table *mpt,
					  Statement    *stm_head,
					  Quadruple    **tmpqpt,
					  Operand      **opt,
					  int          entry,
					  int          idx_entry)
{
    Statement   *spt;
    Quadruple   *qpt,
                *prevqpt,
                *dumyqpt = NULL,
                tmpqr,
                dumyqr;
    Array_table *array_head = NULL;
    int         i;

    for (spt = stm_head; spt != NULL; spt = spt->next) {
	for (qpt = spt->qr_head; qpt != NULL; qpt = qpt->next) {
	    if (qpt->ope == OPE_ASSIGN &&
		qpt->op[0] != NULL &&
		qpt->op[0]->kind == KIND_ARRAY &&
		qpt->op[0]->entry == entry) {
		if ((array_head = search_array_table(mpt->array_head,
						     qpt->op[0]->entry))) {
		    if (check_use_array_for_def_array(spt, qpt, idx_entry)) {
                        if (check_array_subscript_exist_temp(qpt->op[0]->inner)) {
			    collect_subexpression_of_dosum_sum(qpt, &tmpqr, 0);
			    dumyqpt = tmpqr.prev;
			    if (dumyqpt != NULL) {
			        dumyqpt->next = NULL;
				while (dumyqpt->prev)
				  dumyqpt = dumyqpt->prev;
				*tmpqpt = copy_qr_list(dumyqpt);
			    }
			    *opt = copy_operand(qpt->op[0]);
			    for (prevqpt = qpt; prevqpt; prevqpt = prevqpt->prev) {
			        for (i = 1; i < 4; i++) {
				    if (prevqpt->op[i] &&
					prevqpt->op[i]->kind == KIND_ARRAY &&
					prevqpt->op[i]->entry == qpt->op[0]->entry) {
				        collect_subexpression_of_dosum_sum(prevqpt,
									   &dumyqr, i);
				    }
				}
			    }
	  	        }
		    }
		}
	    }
	}
    }
}
