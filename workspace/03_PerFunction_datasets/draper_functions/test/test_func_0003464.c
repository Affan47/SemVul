change_temp_to_scalar_operand(Operand *op, int src_entry, Var_table *dst_var)
{
    if (op->kind == KIND_TEMP && op->entry == src_entry) {
        op->kind = KIND_VAR;
        op->entry = dst_var->entry;
        op->tbl.v = dst_var;
    }

    if (op->next != NULL)
        change_temp_to_scalar_operand(op->next, src_entry, dst_var);

    if (op->inner != NULL)
        change_temp_to_scalar_operand(op->inner, src_entry, dst_var);
}
