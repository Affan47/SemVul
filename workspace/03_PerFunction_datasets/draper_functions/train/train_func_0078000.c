construct_assign_qr( Statement *target_stm,
                     void *dest_tbl, symbol_kind d_kind,
                     void *src_tbl, symbol_kind s_kind )
{
    int d_entry, s_entry;
    Quadruple *assign_qr;
    Operand *op[4];

    switch (d_kind) {
    case  KIND_VAR:
        d_entry = ((Var_table *)dest_tbl)->entry;
        break;
    case  KIND_TEMP:
        d_entry = ((Temp_table *)dest_tbl)->entry;
        break;
    case  KIND_CONST:
        d_entry = ((Const_table *)dest_tbl)->entry;
        break;
    case  KIND_SYNC:
        d_entry = ((Sync_table *)dest_tbl)->entry;
        break;
    default:
        assert(FALSE);
    }

    switch (s_kind) {
    case  KIND_VAR:
        s_entry = ((Var_table *)src_tbl)->entry;
        break;
    case  KIND_TEMP:
        s_entry = ((Temp_table *)src_tbl)->entry;
        break;
    case  KIND_CONST:
        s_entry = ((Const_table *)src_tbl)->entry;
        break;
    case  KIND_SYNC:
        s_entry = ((Sync_table *)src_tbl)->entry;
        break;
    default:
        assert(FALSE);
    }

    op[0] = construct_operand( d_entry, d_kind, dest_tbl );
    op[1] = construct_operand( s_entry, s_kind, src_tbl );
    assign_qr = construct_qr( OPE_ASSIGN, op, 2, target_stm );

    return assign_qr;
}
