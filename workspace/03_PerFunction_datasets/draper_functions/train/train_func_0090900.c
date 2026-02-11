make_array_range_semnode_op(Operand *target_op, Quadruple *qpt)
{
    Array_table *atbl = target_op->tbl.a;
    Array_range_semnode dummy, *range;
    Operand *op;
    int i;
    extern Boolean strict_ud_replace;
    Boolean tmp;

    tmp = strict_ud_replace;
    strict_ud_replace = FALSE;
    range = &dummy;
    for (i = 0, op = target_op->inner;
         i < atbl->dim && op != NULL;
         i++, op = op->next) {
        range->next_dim = alloc_array_range_semnode();
        range = range->next_dim;
        range->lower_tree = make_semtree_operand(qpt->stm->pe_stm->block->module,
                                                 op, qpt);
        replace_semnode_for_ud(range->lower_tree, qpt->stm);
        range->upper_tree = semtree_dup(range->lower_tree);
    }
    strict_ud_replace = tmp;
    return dummy.next_dim;
}
