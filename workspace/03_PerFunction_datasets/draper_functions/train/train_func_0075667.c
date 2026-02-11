dwarf_undef_macro(Dwarf_P_Debug dbg,
    Dwarf_Unsigned line,
    char *macname, Dwarf_Error * error)
{

    size_t len;
    size_t length_est;
    int res;
    int compose_error_type;

    if (dbg == NULL) {
        _dwarf_p_error(NULL, error, DW_DLE_DBG_NULL);
        return (DW_DLV_ERROR);
    }
    if (macname == 0) {
        _dwarf_p_error(NULL, error, DW_DLE_MACINFO_STRING_NULL);
        return (DW_DLV_ERROR);
    }
    len = strlen(macname) + 1;
    if (len == 0) {
        _dwarf_p_error(NULL, error, DW_DLE_MACINFO_STRING_EMPTY);
        return (DW_DLV_ERROR);
    }
    length_est = COMMAND_LEN + LINE_LEN + len;
    res = libdwarf_compose_begin(dbg, DW_MACINFO_undef, length_est,
        &compose_error_type);
    if (res != DW_DLV_OK) {
        _dwarf_p_error(NULL, error, compose_error_type);
        return (DW_DLV_ERROR);
    }
    res = libdwarf_compose_add_line(dbg, line, &compose_error_type);
    if (res != DW_DLV_OK) {
        _dwarf_p_error(NULL, error, compose_error_type);
        return (DW_DLV_ERROR);
    }
    libdwarf_compose_add_string(dbg, macname, len);
    res = libdwarf_compose_complete(dbg, &compose_error_type);
    if (res != DW_DLV_OK) {
        _dwarf_p_error(NULL, error, compose_error_type);
        return (DW_DLV_ERROR);
    }
    return DW_DLV_OK;
}
