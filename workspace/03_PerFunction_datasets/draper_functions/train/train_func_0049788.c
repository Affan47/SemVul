gnc_split_reg2_determine_read_only (GNCSplitReg2 *gsr)
{
    dialog_args *args = g_malloc (sizeof (dialog_args));
    GncTreeViewSplitReg *view;

    if (qof_book_is_readonly (gnc_get_current_book()))
    {


        gsr->read_only = TRUE;
    }

    if (!gsr->read_only)
    {

        switch (gnc_split_reg2_get_placeholder (gsr))
        {
        case PLACEHOLDER_NONE:

            return;

        case PLACEHOLDER_THIS:
            args->string = _("This account may not be edited. If you want "
                             "to edit transactions in this register, please "
                             "open the account options and turn off the "
                             "placeholder checkbox.");
            break;

        default:
            args->string = _("One of the sub-accounts selected may not be "
                             "edited. If you want to edit transactions in "
                             "this register, please open the sub-account "
                             "options and turn off the placeholder checkbox. "
                             "You may also open an individual account instead "
                             "of a set of accounts.");
            break;
        }
        gsr->read_only = TRUE;

        args->gsr = gsr;
        g_timeout_add (250, gtk_callback_bug_workaround, args);
    }
}
