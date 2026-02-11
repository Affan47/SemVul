gnc_split_register_get_action_help (VirtualLocation virt_loc,
                                    gpointer user_data)
{
    SplitRegister *reg = user_data;
    const char *help;

    help = gnc_table_get_entry (reg->table, virt_loc);
    if (!help || *help == '\0')
        help = reg->use_tran_num_for_num_field ?
        _("Enter an action type, or choose one from the list") :
        _("Enter a reference number, such as the next check number, or choose an action type from the list");

    return g_strdup (help);
}
