get_pointer_type_in_ps(Parallel_section *ps, symbol_kind kind, int entry)
{
    Operand *op;
    Type_table *pointer_type = NULL;

    op = get_new_op(ps->layer_block->module, kind, entry);
    switch (op->kind) {
    case KIND_ARRAY:
        pointer_type = get_pointer_type(op, op->tbl.a->dim);
        break;
    case KIND_INVISIBLE:
        pointer_type = get_pointer_type(op, op->tbl.i->dim);
        break;
    case KIND_HEAP:
        pointer_type = get_pointer_type(op, op->tbl.h->dim);
        break;
    default:
        fatal("unexpected kind");
        break;
    }
    free_operand(op);

    return pointer_type;
}
