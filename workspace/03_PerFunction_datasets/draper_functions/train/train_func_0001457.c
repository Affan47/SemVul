dwarf_get_abbrev(Dwarf_Debug dbg,
    Dwarf_Unsigned offset,
    Dwarf_Abbrev * returned_abbrev,
    Dwarf_Unsigned * length,
    Dwarf_Unsigned * abbr_count, Dwarf_Error * error)
{
    Dwarf_Small *abbrev_ptr = 0;
    Dwarf_Small *abbrev_section_end = 0;
    Dwarf_Half attr = 0;
    Dwarf_Half attr_form = 0;
    Dwarf_Abbrev ret_abbrev = 0;
    Dwarf_Unsigned labbr_count = 0;
    Dwarf_Unsigned utmp = 0;


    if (dbg == NULL) {
        _dwarf_error(NULL, error, DW_DLE_DBG_NULL);
        return (DW_DLV_ERROR);
    }
    if (dbg->de_debug_abbrev.dss_data == 0) {


        int res = _dwarf_load_debug_info(dbg, error);

        if (res != DW_DLV_OK) {
            return res;
        }
    }

    if (offset >= dbg->de_debug_abbrev.dss_size) {
        return (DW_DLV_NO_ENTRY);
    }


    ret_abbrev = (Dwarf_Abbrev) _dwarf_get_alloc(dbg, DW_DLA_ABBREV, 1);
    if (ret_abbrev == NULL) {
        _dwarf_error(dbg, error, DW_DLE_ALLOC_FAIL);
        return (DW_DLV_ERROR);
    }
    ret_abbrev->ab_dbg = dbg;
    if (returned_abbrev == 0 || abbr_count == 0) {
        dwarf_dealloc(dbg, ret_abbrev, DW_DLA_ABBREV);
        _dwarf_error(dbg, error, DW_DLE_DWARF_ABBREV_NULL);
        return (DW_DLV_ERROR);
    }


    *abbr_count = 0;
    if (length != NULL)
        *length = 1;

    abbrev_ptr = dbg->de_debug_abbrev.dss_data + offset;
    abbrev_section_end =
        dbg->de_debug_abbrev.dss_data + dbg->de_debug_abbrev.dss_size;

    DECODE_LEB128_UWORD(abbrev_ptr, utmp);
    ret_abbrev->ab_code = (Dwarf_Word) utmp;
    if (ret_abbrev->ab_code == 0) {
        *returned_abbrev = ret_abbrev;
        *abbr_count = 0;
        if (length) {
            *length = 1;
        }
        return (DW_DLV_OK);
    }

    DECODE_LEB128_UWORD(abbrev_ptr, utmp);
    ret_abbrev->ab_tag = utmp;
    ret_abbrev->ab_has_child = *(abbrev_ptr++);
    ret_abbrev->ab_abbrev_ptr = abbrev_ptr;

    do {
        Dwarf_Unsigned utmp2;

        DECODE_LEB128_UWORD(abbrev_ptr, utmp2);
        attr = (Dwarf_Half) utmp2;
        DECODE_LEB128_UWORD(abbrev_ptr, utmp2);
        attr_form = (Dwarf_Half) utmp2;

        if (attr != 0)
            (labbr_count)++;

    } while (abbrev_ptr < abbrev_section_end &&
        (attr != 0 || attr_form != 0));

    if (abbrev_ptr > abbrev_section_end) {
        dwarf_dealloc(dbg, ret_abbrev, DW_DLA_ABBREV);
        _dwarf_error(dbg, error, DW_DLE_ABBREV_DECODE_ERROR);
        return (DW_DLV_ERROR);
    }

    if (length != NULL)
        *length = abbrev_ptr - dbg->de_debug_abbrev.dss_data - offset;

    *returned_abbrev = ret_abbrev;
    *abbr_count = labbr_count;
    return (DW_DLV_OK);
}
