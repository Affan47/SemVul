check_index_boundary(Operand *op, int line_no)
{
    Operand *tmpop;
    Array_table *apt;
    int i;

    if (op->kind != KIND_ARRAY)
	return;

    apt = op->tbl.a;
    for (tmpop = op->inner, i = 0;
	 tmpop != NULL;
	 tmpop = tmpop->next, i++) {
	if (tmpop->kind == KIND_CONST) {
	    if (apt->lim.ct[i] < tmpop->tbl.c->val.i) {
		print_error_msg(OUTSIDE_BOUNDARY, line_no);
	    }
	}
    }
}
