_dwarf_get_size_of_val(Dwarf_Debug dbg,
    Dwarf_Unsigned form,
    Dwarf_Half address_size,
    Dwarf_Small * val_ptr, int v_length_size)
{
    Dwarf_Unsigned length = 0;
    Dwarf_Word leb128_length = 0;
    Dwarf_Unsigned form_indirect = 0;
    Dwarf_Unsigned ret_value = 0;

    switch (form) {

    default:
        return (form);

    case DW_FORM_addr:
        if(address_size) {
            return address_size;
        }

        return (dbg->de_pointer_size);
    case DW_FORM_ref_sig8:
        return 8;


    case DW_FORM_ref_addr:
        return (v_length_size);

    case DW_FORM_block1:
        return (*(Dwarf_Small *) val_ptr + 1);

    case DW_FORM_block2:
        READ_UNALIGNED(dbg, ret_value, Dwarf_Unsigned,
            val_ptr, sizeof(Dwarf_Half));
        return (ret_value + sizeof(Dwarf_Half));

    case DW_FORM_block4:
        READ_UNALIGNED(dbg, ret_value, Dwarf_Unsigned,
            val_ptr, sizeof(Dwarf_ufixed));
        return (ret_value + sizeof(Dwarf_ufixed));


    case DW_FORM_data1:
        return (1);

    case DW_FORM_data2:
        return (2);

    case DW_FORM_data4:
        return (4);

    case DW_FORM_data8:
        return (8);

    case DW_FORM_string:
        return (strlen((char *) val_ptr) + 1);

    case DW_FORM_block:
    case DW_FORM_exprloc:
        length = _dwarf_decode_u_leb128(val_ptr, &leb128_length);
        return (length + leb128_length);

    case DW_FORM_flag_present:
        return (0);
    case DW_FORM_flag:
        return (1);

    case DW_FORM_sec_offset:

        return (v_length_size);

    case DW_FORM_ref_udata:


        _dwarf_decode_u_leb128(val_ptr, &leb128_length);
        return (leb128_length);

    case DW_FORM_indirect:
        {
            Dwarf_Word indir_len = 0;

            form_indirect = _dwarf_decode_u_leb128(val_ptr, &indir_len);
            if (form_indirect == DW_FORM_indirect) {
                return (0);


            }
            return (indir_len + _dwarf_get_size_of_val(dbg,
                form_indirect,
                address_size,
                val_ptr + indir_len,
                v_length_size));
        }

    case DW_FORM_ref1:
        return (1);

    case DW_FORM_ref2:
        return (2);

    case DW_FORM_ref4:
        return (4);

    case DW_FORM_ref8:
        return (8);

    case DW_FORM_sdata:


        _dwarf_decode_s_leb128(val_ptr, &leb128_length);
        return (leb128_length);

    case DW_FORM_strp:
        return (v_length_size);

    case DW_FORM_udata:


        _dwarf_decode_u_leb128(val_ptr, &leb128_length);
        return (leb128_length);
    }
}
