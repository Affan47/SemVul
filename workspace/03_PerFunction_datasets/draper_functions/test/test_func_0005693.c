dwarf_attr_offset(Dwarf_Die die, Dwarf_Attribute attr,
    Dwarf_Off * offset ,
    Dwarf_Error * error)
{
    Dwarf_Off attroff = 0;
    Dwarf_Small *dataptr = 0;
    Dwarf_Debug dbg = 0;

    CHECK_DIE(die, DW_DLV_ERROR);
    dbg = die->di_cu_context->cc_dbg;
    dataptr = die->di_is_info? dbg->de_debug_info.dss_data:
        dbg->de_debug_types.dss_data;

    attroff = (attr->ar_debug_ptr - dataptr);
    *offset = attroff;
    return DW_DLV_OK;
}
