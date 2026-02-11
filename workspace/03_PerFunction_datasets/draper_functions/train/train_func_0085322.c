gnc_split_register_get_ddue_io_flags (VirtualLocation virt_loc,
                                      gpointer user_data)
{
    SplitRegister *reg = user_data;
    char type;

    type = gnc_split_register_get_type_value (reg, virt_loc);


    if (type != TXN_TYPE_INVOICE)
    {
        return XACC_CELL_ALLOW_NONE;
    }

    return XACC_CELL_ALLOW_READ_ONLY;
}
