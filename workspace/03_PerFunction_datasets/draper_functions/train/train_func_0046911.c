get_basic_section_data(Dwarf_Debug dbg,
    struct Dwarf_Section_s *secdata,
    struct Dwarf_Obj_Access_Section_s *doas,
    Dwarf_Half section_index,
    Dwarf_Error* error,
    int duperr, int emptyerr )
{


    if (secdata->dss_index != 0) {
        DWARF_DBG_ERROR(dbg, duperr, DW_DLV_ERROR);
    }
    if (doas->size == 0) {
        if (emptyerr == 0 ) {

            return DW_DLV_OK;
        }

        DWARF_DBG_ERROR(dbg, emptyerr, DW_DLV_ERROR);
    }
    secdata->dss_index = section_index;
    secdata->dss_size = doas->size;
    secdata->dss_addr = doas->addr;
    secdata->dss_link = doas->link;
    secdata->dss_entrysize = doas->entrysize;
    return DW_DLV_OK;
}
