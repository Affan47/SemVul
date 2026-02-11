variable_is_argument(int entry, symbol_kind kind, Module_table *mpt)
{
    Operand *op;
    for (op = mpt->arg_head; op != NULL; op = op->next) {
        if (op->entry == entry && op->kind == kind)
            return TRUE;
    }

    return FALSE;
}
