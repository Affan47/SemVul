make_equivalence_for_type_mismatch(Module_table *callee,
                                   Operand *real_op,
                                   symbol_kind kind,
                                   void *tbl)
{
    Common_table *ct;
    Common_node *real_node;
    symbol_kind real_kind = real_op->kind;
    void *real_tbl = NULL;
    int offset = 0;

    switch (real_kind) {
    case KIND_VAR:
        offset = 0;
        real_tbl = real_op->tbl.v;
        break;
    case KIND_ARRAY:
        offset = get_real_array_offset(real_op);
        real_tbl = real_op->tbl.a;
        break;
    default:
        fatal("make_equivalence_for_type_mimatch(): "
              "unexpected operand type: %d\n",
              real_op->kind);
    }

    real_node = operand_common_node(real_op);
    if (real_node == NULL) {
        ct = make_empty_equivalence_in_module(callee);
        make_common_node_for_symbol(real_kind, real_tbl, ct, DB_EQUIVALENCE, 0);
        make_common_node_for_symbol(kind, tbl, ct, DB_EQUIVALENCE, offset);
    } else {
        ct = real_node->parent;
        make_common_node_for_symbol(kind,
                                    tbl,
                                    ct,
                                    real_node->kind,
                                    real_node->offset + offset);
    }
}
