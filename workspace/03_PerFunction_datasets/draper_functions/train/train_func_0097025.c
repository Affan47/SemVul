dwarf_add_AT_unsigned_const(Dwarf_P_Debug dbg,
   Dwarf_P_Die ownerdie,
   Dwarf_Half attr,
   Dwarf_Unsigned value, Dwarf_Error * error)
{
    Dwarf_P_Attribute new_attr = 0;
    Dwarf_Half attr_form = 0;
    Dwarf_Small size = 0;

    if (dbg == NULL) {
        _dwarf_p_error(NULL, error, DW_DLE_DBG_NULL);
        return ((Dwarf_P_Attribute) DW_DLV_BADADDR);
    }

    if (ownerdie == NULL) {
        _dwarf_p_error(dbg, error, DW_DLE_DIE_NULL);
        return ((Dwarf_P_Attribute) DW_DLV_BADADDR);
    }

    switch (attr) {
    case DW_AT_ordering:
    case DW_AT_byte_size:
    case DW_AT_bit_offset:
    case DW_AT_bit_size:
    case DW_AT_inline:
    case DW_AT_language:
    case DW_AT_visibility:
    case DW_AT_virtuality:
    case DW_AT_accessibility:
    case DW_AT_address_class:
    case DW_AT_calling_convention:
    case DW_AT_encoding:
    case DW_AT_identifier_case:
    case DW_AT_MIPS_loop_unroll_factor:
    case DW_AT_MIPS_software_pipeline_depth:
        break;

    case DW_AT_decl_column:
    case DW_AT_decl_file:
    case DW_AT_decl_line:
    case DW_AT_const_value:
    case DW_AT_start_scope:
    case DW_AT_stride_size:
    case DW_AT_count:
    case DW_AT_associated:
    case DW_AT_allocated:
    case DW_AT_upper_bound:
    case DW_AT_lower_bound:
    case DW_AT_call_file:
    case DW_AT_call_line:
        break;

    default:
        if ( attr < DW_AT_lo_user || attr > DW_AT_hi_user ) {
            _dwarf_p_error(dbg, error, DW_DLE_INPUT_ATTR_BAD);
            return ((Dwarf_P_Attribute) DW_DLV_BADADDR);
        }
        break;
    }


    if (value <= UCHAR_MAX) {
        attr_form = DW_FORM_data1;
        size = 1;
    } else if (value <= USHRT_MAX) {
        attr_form = DW_FORM_data2;
        size = 2;
    } else if (value <= UINT_MAX) {
        attr_form = DW_FORM_data4;
        size = 4;
    } else {
        attr_form = DW_FORM_data8;
        size = 8;
    }

    new_attr = (Dwarf_P_Attribute)
        _dwarf_p_get_alloc(dbg, sizeof(struct Dwarf_P_Attribute_s));
    if (new_attr == NULL) {
        _dwarf_p_error(dbg, error, DW_DLE_ALLOC_FAIL);
        return ((Dwarf_P_Attribute) DW_DLV_BADADDR);
    }

    new_attr->ar_attribute = attr;
    new_attr->ar_attribute_form = attr_form;
    new_attr->ar_rel_type = R_MIPS_NONE;
    new_attr->ar_reloc_len = 0;
    new_attr->ar_nbytes = size;
    new_attr->ar_next = 0;

    new_attr->ar_data = (char *)
        _dwarf_p_get_alloc(dbg, size);
    if (new_attr->ar_data == NULL) {
        _dwarf_p_error(dbg, error, DW_DLE_ALLOC_FAIL);
        return ((Dwarf_P_Attribute) DW_DLV_BADADDR);
    }
    WRITE_UNALIGNED(dbg, new_attr->ar_data,
        (const void *) &value, sizeof(value), size);


    _dwarf_pro_add_at_to_die(ownerdie, new_attr);
    return new_attr;
}
