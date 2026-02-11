_dwarf_pro_add_line_entry(Dwarf_P_Debug dbg,
    Dwarf_Unsigned file_index,
    Dwarf_Addr code_address,
    Dwarf_Unsigned symidx,
    Dwarf_Unsigned line_no,
    Dwarf_Signed col_no,
    Dwarf_Bool is_stmt_begin,
    Dwarf_Bool is_bb_begin,
    Dwarf_Ubyte opc,
    Dwarf_Bool isepilbeg,
    Dwarf_Bool isprolend,
    Dwarf_Unsigned isa,
    Dwarf_Unsigned discriminator,
    Dwarf_Error * error)
{
    if (dbg->de_lines == NULL) {
        dbg->de_lines = (Dwarf_P_Line)
            _dwarf_p_get_alloc(dbg, sizeof(struct Dwarf_P_Line_s));
        if (dbg->de_lines == NULL) {
            DWARF_P_DBG_ERROR(dbg, DW_DLE_LINE_ALLOC, DW_DLV_NOCOUNT);
        }
        dbg->de_last_line = dbg->de_lines;
        _dwarf_pro_reg_init(dbg,dbg->de_lines);

    } else {
        dbg->de_last_line->dpl_next = (Dwarf_P_Line)
            _dwarf_p_get_alloc(dbg, sizeof(struct Dwarf_P_Line_s));
        if (dbg->de_last_line->dpl_next == NULL) {
            DWARF_P_DBG_ERROR(dbg, DW_DLE_LINE_ALLOC, DW_DLV_NOCOUNT);
        }
        dbg->de_last_line = dbg->de_last_line->dpl_next;
        _dwarf_pro_reg_init(dbg,dbg->de_last_line);
    }
    dbg->de_last_line->dpl_address = code_address;
    dbg->de_last_line->dpl_file = (unsigned long) file_index;
    dbg->de_last_line->dpl_line = (unsigned long) line_no;
    dbg->de_last_line->dpl_column = (unsigned long) col_no;
    dbg->de_last_line->dpl_is_stmt = is_stmt_begin;
    dbg->de_last_line->dpl_basic_block = is_bb_begin;
    dbg->de_last_line->dpl_opc = opc;
    dbg->de_last_line->dpl_r_symidx = symidx;
    dbg->de_last_line->dpl_prologue_end = isprolend;
    dbg->de_last_line->dpl_epilogue_begin = isepilbeg;
    dbg->de_last_line->dpl_isa = isa;
    dbg->de_last_line->dpl_discriminator = discriminator;
    return (0);
}
