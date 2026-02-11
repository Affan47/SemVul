dwarf_formstring(Dwarf_Attribute attr,
    char **return_str, Dwarf_Error * error)
{
    Dwarf_CU_Context cu_context = 0;
    Dwarf_Debug dbg = 0;
    Dwarf_Unsigned offset = 0;
    int res = DW_DLV_ERROR;

    res  = get_attr_dbg(&dbg,&cu_context,attr,error);
    if(res != DW_DLV_OK) {
        return res;
    }
    if (attr->ar_attribute_form == DW_FORM_string) {

        void *begin = attr->ar_debug_ptr;

        if (0 == dbg->de_assume_string_in_bounds) {


            void *end = dbg->de_debug_info.dss_data +
                cu_context->cc_debug_offset +
                cu_context->cc_length + cu_context->cc_length_size +
                cu_context->cc_extension_size;
            if (0 == _dwarf_string_valid(begin, end)) {
                _dwarf_error(dbg, error, DW_DLE_ATTR_FORM_SIZE_BAD);
                return (DW_DLV_ERROR);
            }
        }
        *return_str = (char *) (begin);
        return DW_DLV_OK;
    }

    if (attr->ar_attribute_form == DW_FORM_strp) {
        READ_UNALIGNED(dbg, offset, Dwarf_Unsigned,
            attr->ar_debug_ptr,
            cu_context->cc_length_size);

        res = _dwarf_load_section(dbg, &dbg->de_debug_str,error);
        if (res != DW_DLV_OK) {
            return res;
        }
        if (0 == dbg->de_assume_string_in_bounds) {


            void *end = dbg->de_debug_str.dss_data +
                dbg->de_debug_str.dss_size;
            void*begin = dbg->de_debug_str.dss_data + offset;
            if (0 == _dwarf_string_valid(begin, end)) {
                _dwarf_error(dbg, error, DW_DLE_STRP_OFFSET_BAD);
                return (DW_DLV_ERROR);
            }
        }


        if (offset >= dbg->de_debug_str.dss_size) {
            _dwarf_error(dbg, error, DW_DLE_DEBUG_STR_OFFSET_BAD);
            return (DW_DLV_ERROR);
        }

        *return_str = (char *) (dbg->de_debug_str.dss_data + offset);
        return DW_DLV_OK;
    }

    _dwarf_error(dbg, error, DW_DLE_ATTR_FORM_BAD);
    return (DW_DLV_ERROR);
}
