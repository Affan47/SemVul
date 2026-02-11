dwarf_get_fde_info_for_reg3(Dwarf_Fde fde,
    Dwarf_Half table_column,
    Dwarf_Addr pc_requested,
    Dwarf_Small * value_type,
    Dwarf_Signed * offset_relevant,
    Dwarf_Signed * register_num,
    Dwarf_Signed * offset_or_block_len,
    Dwarf_Ptr * block_ptr,
    Dwarf_Addr * row_pc_out,
    Dwarf_Error * error)
{
    struct Dwarf_Frame_s fde_table;
    int res = DW_DLV_ERROR;

    Dwarf_Debug dbg = 0;
    int table_real_data_size = 0;

    FDE_NULL_CHECKS_AND_SET_DBG(fde, dbg);
    table_real_data_size = dbg->de_frame_reg_rules_entry_count;
    res = dwarf_initialize_fde_table(dbg, &fde_table,
        table_real_data_size, error);
    if (res != DW_DLV_OK)
        return res;
    if (table_column >= table_real_data_size) {
        dwarf_free_fde_table(&fde_table);
        _dwarf_error(dbg, error, DW_DLE_FRAME_TABLE_COL_BAD);
        return (DW_DLV_ERROR);
    }


    res = _dwarf_get_fde_info_for_a_pc_row(fde, pc_requested, &fde_table,
        dbg->de_frame_cfa_col_number,
        error);
    if (res != DW_DLV_OK) {
        dwarf_free_fde_table(&fde_table);
        return res;
    }

    if (register_num != NULL)
        *register_num = fde_table.fr_reg[table_column].ru_register;
    if (offset_or_block_len != NULL)
        *offset_or_block_len =
            fde_table.fr_reg[table_column].ru_offset_or_block_len;
    if (row_pc_out != NULL)
        *row_pc_out = fde_table.fr_loc;
    if (block_ptr)
        *block_ptr = fde_table.fr_reg[table_column].ru_block;


    *value_type = fde_table.fr_reg[table_column].ru_value_type;
    *offset_relevant = (fde_table.fr_reg[table_column].ru_is_off);
    dwarf_free_fde_table(&fde_table);
    return DW_DLV_OK;

}
