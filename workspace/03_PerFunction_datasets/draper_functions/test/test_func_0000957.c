lad_sm_change_index_in_sub(StripMiningInnerLoop *smil,
			   Quadruple *qr,
			   Operand *arg,
			   SemTree *new_index)
{
    Operand *ope, *prev_op, *new_index_op;
    SemTree *op_sem, *old_index;
    int i;

    i = 0;

    prev_op = NULL;
    for (ope = arg->inner; ope != NULL; ope = ope->next) {
	if (ope->kind == KIND_VAR && !lad_sm_check_array_inner_operand(qr)) {
	    op_sem = make_semtree_scalar(smil->block->module, ope->tbl.v);
	    old_index = lad_sm_get_smil_range_index(smil);

	    if (lad_sm_check_same_var_operand(old_index, op_sem)) {
		new_index_op = get_new_op_var(semtree_to_scalar(new_index));
		if (opt_lad_sm_cmp_debug) {
		    printf("new_index_var entry : %d\n", new_index_op->entry);
		    printf("old_index_var entry : %d\n", ope->tbl.v->entry);
		    printf("i : %d\n", i);
		}
		if (prev_op == NULL) {
		    arg->inner = new_index_op;
		} else {
		    prev_op->next = new_index_op;
		}
		new_index_op->next = ope->next;
	    }
	}
	prev_op = ope;
	i++;
    }
}
