dwarf_expr_reset(Dwarf_P_Expr expr, Dwarf_Error * error)
{
    if (expr == NULL) {
        _dwarf_p_error(NULL, error, DW_DLE_EXPR_NULL);
        return;
    }
    expr->ex_next_byte_offset=0;
}
