copy_op_entry_list(Op_entry *op_entry_l)
{
    Op_entry *op_e, *new_op_e;
    Op_entry *new_op_l = NULL;
    Op_entry *new_last = NULL;

    for (op_e = op_entry_l; op_e != NULL; op_e = op_e->next) {
        new_op_e = get_new_op_entry(op_e->entry, op_e->kind, NULL);
        if (new_last == NULL) {
            new_op_l = new_op_e;
        }
        else {
            new_last->next = new_op_e;
        }
        new_last = new_op_e;
    }

    return new_op_l;
}
