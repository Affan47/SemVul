gppot_filter_response_cb (GtkWidget *dialog,
                          gint       response,
                          OwnerFilterDialog *fd)
{
    gpointer gptemp;

    g_return_if_fail(GTK_IS_DIALOG(dialog));

    ENTER("dialog %p, response %d", dialog, response);

    if (response != GTK_RESPONSE_OK)
    {
        fd->show_inactive = fd->original_show_inactive;
        fd->show_zero_total = fd->original_show_zero_total;
        gnc_tree_view_owner_refilter(fd->tree_view);
    }


    gptemp = (gpointer *)fd->dialog;
    g_atomic_pointer_compare_and_exchange(&gptemp,
                                          dialog, NULL);
    fd->dialog = gptemp;
    gtk_widget_destroy(dialog);
    LEAVE("");
}
