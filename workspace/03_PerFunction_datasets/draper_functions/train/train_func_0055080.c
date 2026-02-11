csv_import_trans_auto_cb (GtkWidget *cb, gpointer user_data )
{
    CsvImportTrans *info = user_data;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb)))
    {
        if (info->previewing_errors == TRUE)
            info->approved = TRUE;
        else
            info->account_picker->auto_create = TRUE;
    }
    else
    {
        if (info->previewing_errors == TRUE)
            info->approved = FALSE;
        else
            info->account_picker->auto_create = FALSE;
    }
}
