dwarf_fde_cfa_offset(Dwarf_P_Fde fde,
    Dwarf_Unsigned reg,
    Dwarf_Signed offset, Dwarf_Error * error)
{
    Dwarf_Ubyte opc, regno;
    char *ptr = 0;
    Dwarf_P_Frame_Pgm curinst;
    int nbytes = 0;
    int res = 0;
    char buff1[ENCODE_SPACE_NEEDED];
    Dwarf_P_Debug dbg = fde->fde_dbg;

    curinst = (Dwarf_P_Frame_Pgm)
        _dwarf_p_get_alloc(dbg, sizeof(struct Dwarf_P_Frame_Pgm_s));
    if (curinst == NULL) {
        DWARF_P_DBG_ERROR(dbg, DW_DLE_FPGM_ALLOC,
            (Dwarf_P_Fde) DW_DLV_BADADDR);
    }
    opc = DW_CFA_offset;
    regno = reg;
    if (regno & 0xc0) {
        DWARF_P_DBG_ERROR(dbg, DW_DLE_REGNO_OVFL,
            (Dwarf_P_Fde) DW_DLV_BADADDR);
    }
    opc = opc | regno;
    curinst->dfp_opcode = opc;
    res = _dwarf_pro_encode_leb128_nm(offset, &nbytes,
        buff1, sizeof(buff1));
    if (res != DW_DLV_OK) {
        _dwarf_p_error(dbg, error, DW_DLE_STRING_ALLOC);
        return ((Dwarf_P_Fde) DW_DLV_BADADDR);
    }
    ptr = (char *) _dwarf_p_get_alloc(dbg, nbytes);
    if (ptr == NULL) {
        _dwarf_p_error(dbg, error, DW_DLE_STRING_ALLOC);
        return ((Dwarf_P_Fde) DW_DLV_BADADDR);
    }
    memcpy(ptr, buff1, nbytes);

    curinst->dfp_args = ptr;
    curinst->dfp_nbytes = nbytes;
    curinst->dfp_next = NULL;

    _dwarf_pro_add_to_fde(fde, curinst);
    return fde;
}
