search_operand_op(Operand *op, Var_map *var_map_head, Module_table *mod_sb)
{
    convert_operand(var_map_head, op, mod_sb);

    if(op->next != NULL) {
        search_operand_op(op->next, var_map_head, mod_sb);
    }

    if(op->inner != NULL) {
        search_operand_op(op->inner, var_map_head, mod_sb);
    }

}
