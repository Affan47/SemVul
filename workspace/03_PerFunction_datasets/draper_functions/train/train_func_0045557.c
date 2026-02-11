dwarf_get_cie_info(Dwarf_Cie cie,
    Dwarf_Unsigned * bytes_in_cie,
    Dwarf_Small * ptr_to_version,
    char **augmenter,
    Dwarf_Unsigned * code_alignment_factor,
    Dwarf_Signed * data_alignment_factor,
    Dwarf_Half * return_address_register,
    Dwarf_Ptr * initial_instructions,
    Dwarf_Unsigned * initial_instructions_length,
    Dwarf_Error * error)
{
    Dwarf_Debug dbg;

    if (cie == NULL) {
        _dwarf_error(NULL, error, DW_DLE_CIE_NULL);
        return (DW_DLV_ERROR);
    }

    dbg = cie->ci_dbg;
    if (dbg == NULL) {
        _dwarf_error(NULL, error, DW_DLE_CIE_DBG_NULL);
        return (DW_DLV_ERROR);
    }

    if (ptr_to_version != NULL)
        *ptr_to_version = cie->ci_cie_version_number;
    if (augmenter != NULL)
        *augmenter = cie->ci_augmentation;
    if (code_alignment_factor != NULL)
        *code_alignment_factor = cie->ci_code_alignment_factor;
    if (data_alignment_factor != NULL)
        *data_alignment_factor = cie->ci_data_alignment_factor;
    if (return_address_register != NULL)
        *return_address_register = cie->ci_return_address_register;
    if (initial_instructions != NULL)
        *initial_instructions = cie->ci_cie_instr_start;
    if (initial_instructions_length != NULL) {
        *initial_instructions_length = cie->ci_length +
            cie->ci_length_size +
            cie->ci_extension_size -
            (cie->ci_cie_instr_start - cie->ci_cie_start);

    }
    *bytes_in_cie = (cie->ci_length);
    return (DW_DLV_OK);
}
