dwarf_object_init(Dwarf_Obj_Access_Interface* obj, Dwarf_Handler errhand,
    Dwarf_Ptr errarg, Dwarf_Debug* ret_dbg,
    Dwarf_Error* error)
{
    Dwarf_Debug dbg = 0;
    int setup_result = DW_DLV_OK;

    dbg = _dwarf_get_debug();
    if (dbg == NULL) {
        DWARF_DBG_ERROR(dbg, DW_DLE_DBG_ALLOC, DW_DLV_ERROR);
    }
    dbg->de_errhand = errhand;
    dbg->de_errarg = errarg;
    dbg->de_frame_rule_initial_value = DW_FRAME_REG_INITIAL_VALUE;
    dbg->de_frame_reg_rules_entry_count = DW_FRAME_LAST_REG_NUM;
#ifdef HAVE_OLD_FRAME_CFA_COL


    dbg->de_frame_cfa_col_number = DW_FRAME_CFA_COL;
#else
    dbg->de_frame_cfa_col_number = DW_FRAME_CFA_COL3;
#endif
    dbg->de_frame_same_value_number = DW_FRAME_SAME_VAL;
    dbg->de_frame_undefined_value_number  = DW_FRAME_UNDEFINED_VAL;

    dbg->de_obj_file = obj;

    setup_result = _dwarf_setup(dbg, error);
    if (setup_result != DW_DLV_OK) {


        int freeresult = _dwarf_free_all_of_one_debug(dbg);
        if (freeresult == DW_DLV_ERROR) {
            DWARF_DBG_ERROR(dbg, DW_DLE_DBG_ALLOC, DW_DLV_ERROR);
        }
        dwarf_malloc_check_complete("After Final free");
        return setup_result;
    }

    dwarf_harmless_init(&dbg->de_harmless_errors,
        DW_HARMLESS_ERROR_CIRCULAR_LIST_DEFAULT_SIZE);


    _dwarf_setup_debug(dbg);


    *ret_dbg = dbg;
    return DW_DLV_OK;
}
