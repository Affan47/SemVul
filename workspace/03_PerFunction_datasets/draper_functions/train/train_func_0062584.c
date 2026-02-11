dwarf_global_formref(Dwarf_Attribute attr,
    Dwarf_Off * ret_offset, Dwarf_Error * error)
{
    Dwarf_Debug dbg = 0;
    Dwarf_Unsigned offset = 0;
    Dwarf_CU_Context cu_context = 0;
    Dwarf_Half context_version = 0;

    int res  = get_attr_dbg(&dbg,&cu_context,attr,error);
    if(res != DW_DLV_OK) {
        return res;
    }
    context_version = cu_context->cc_version_stamp;
    switch (attr->ar_attribute_form) {

    case DW_FORM_ref1:
        offset = *(Dwarf_Small *) attr->ar_debug_ptr;
        goto fixoffset;

    case DW_FORM_ref2:
        READ_UNALIGNED(dbg, offset, Dwarf_Unsigned,
            attr->ar_debug_ptr, sizeof(Dwarf_Half));
        goto fixoffset;

    case DW_FORM_ref4:
        READ_UNALIGNED(dbg, offset, Dwarf_Unsigned,
            attr->ar_debug_ptr, sizeof(Dwarf_ufixed));
        goto fixoffset;

    case DW_FORM_ref8:
        READ_UNALIGNED(dbg, offset, Dwarf_Unsigned,
            attr->ar_debug_ptr, sizeof(Dwarf_Unsigned));
        goto fixoffset;

    case DW_FORM_ref_udata:
        offset = _dwarf_decode_u_leb128(attr->ar_debug_ptr, NULL);

        fixoffset:


        if (offset >= cu_context->cc_length +
            cu_context->cc_length_size +
            cu_context->cc_extension_size) {
            _dwarf_error(dbg, error, DW_DLE_ATTR_FORM_OFFSET_BAD);
            return (DW_DLV_ERROR);
        }


        offset += cu_context->cc_debug_offset;
        break;


    case DW_FORM_data4:
        if(context_version == DW_CU_VERSION4) {
            _dwarf_error(dbg, error, DW_DLE_NOT_REF_FORM);
            return (DW_DLV_ERROR);
        }
        READ_UNALIGNED(dbg, offset, Dwarf_Unsigned,
            attr->ar_debug_ptr, sizeof(Dwarf_ufixed));

        break;
    case DW_FORM_data8:
        if(context_version == DW_CU_VERSION4) {
            _dwarf_error(dbg, error, DW_DLE_NOT_REF_FORM);
            return (DW_DLV_ERROR);
        }
        READ_UNALIGNED(dbg, offset, Dwarf_Unsigned,
            attr->ar_debug_ptr, sizeof(Dwarf_Unsigned));

        break;
    case DW_FORM_ref_addr:
    case DW_FORM_sec_offset:
        {


            unsigned length_size = cu_context->cc_length_size;
            if(length_size == 4) {
                READ_UNALIGNED(dbg, offset, Dwarf_Unsigned,
                    attr->ar_debug_ptr, sizeof(Dwarf_ufixed));
            } else if (length_size == 8) {
                READ_UNALIGNED(dbg, offset, Dwarf_Unsigned,
                    attr->ar_debug_ptr, sizeof(Dwarf_Unsigned));
            } else {
                _dwarf_error(dbg, error, DW_DLE_FORM_SEC_OFFSET_LENGTH_BAD);
                return (DW_DLV_ERROR);
            }
        }
        break;
    case DW_FORM_ref_sig8:


        _dwarf_error(dbg, error, DW_DLE_REF_SIG8_NOT_HANDLED);
        return (DW_DLV_ERROR);
    default:
        _dwarf_error(dbg, error, DW_DLE_BAD_REF_FORM);
        return (DW_DLV_ERROR);
    }


    *ret_offset = offset;
    return DW_DLV_OK;
}
