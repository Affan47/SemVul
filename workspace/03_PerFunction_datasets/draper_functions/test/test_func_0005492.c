gnc_split_register_get_due_date_entry (VirtualLocation virt_loc,
                                       gboolean translate,
                                       gboolean *conditionally_changed,
                                       gpointer user_data)
{
    SplitRegister *reg = user_data;
    Transaction *trans;
    Split *split;
    Timespec ts;
    gboolean is_current;
    char type;

    is_current = virt_cell_loc_equal (reg->table->current_cursor_loc.vcell_loc,
                                      virt_loc.vcell_loc);

    if (is_current)
    {
        type = gnc_split_register_get_type_value (reg, virt_loc);
    }
    else
    {
        const char *typestr =
            gnc_split_register_get_type_entry (virt_loc, translate,
                                               conditionally_changed, user_data);
        if (typestr != NULL)
            type = *typestr;
        else
            type = '\0';
    }


    if (type != TXN_TYPE_INVOICE)
    {

        return NULL;
    }

    split = gnc_split_register_get_split (reg, virt_loc.vcell_loc);
    trans = xaccSplitGetParent (split);
    if (!trans)
    {

        return NULL;
    }

    xaccTransGetDateDueTS (trans, &ts);


    return gnc_print_date (ts);
}
