compare_operand_in_detail (Operand *op1, Operand *op2)
{
    int dim;

    if (op1 && op2 &&
        (op1->kind == op2->kind) && (op1->entry == op2->entry)){
        if (op1->kind == KIND_ARRAY) {
	    if (op1->tbl.a->dim != op2->tbl.a->dim) {
		return FALSE;
	    }
            for (dim = 0; dim < op1->tbl.a->dim; dim++) {
                if (!(compare_sub_data_in_detail (op1->sub[dim],
                                                  op2->sub[dim]))) {
                    return (FALSE);
                }
            }
            return (TRUE);
        } else {
            return (TRUE);
        }
    } else if ((op1 == NULL) && (op2 == NULL)) {
        return (TRUE);
    }

    return (FALSE);
}
