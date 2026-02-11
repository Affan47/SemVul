GTKCreateDialog(const char *szTitle, const dialogtype dt,
                GtkWidget * parent, int flags, GCallback okFun, void *okFunData)
{
    CallbackStruct *cbData;
    GtkWidget *pwDialog, *pwHbox, *pwPixmap;
    GtkAccelGroup *pag;
    int fQuestion = (dt == DT_QUESTION || dt == DT_AREYOUSURE);

    pwDialog = gtk_dialog_new();
    if (flags & DIALOG_FLAG_MINMAXBUTTONS)
        gtk_window_set_type_hint(GTK_WINDOW(pwDialog), GDK_WINDOW_TYPE_HINT_NORMAL);
    gtk_window_set_title(GTK_WINDOW(pwDialog), szTitle);

    if (parent == NULL)
        parent = GTKGetCurrentParent();
    if (!GTK_IS_WINDOW(parent))
        parent = gtk_widget_get_toplevel(parent);
    if (parent && !gtk_widget_get_realized(parent))

        parent = NULL;
    if (parent && GTK_IS_WINDOW(parent))
        gtk_window_present(GTK_WINDOW(parent));
    if (parent != NULL)
        gtk_window_set_transient_for(GTK_WINDOW(pwDialog), GTK_WINDOW(parent));

    if ((flags & DIALOG_FLAG_MODAL) && !(flags & DIALOG_FLAG_NOTIDY))
        g_signal_connect(G_OBJECT(pwDialog), "destroy", G_CALLBACK(quitter), parent);

    pag = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(pwDialog), pag);

    pwHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(pwDialog))), pwHbox);

    if (dt != DT_CUSTOM) {
        pwPixmap = gtk_image_new_from_stock(aszStockItem[dt], GTK_ICON_SIZE_DIALOG);
        gtk_misc_set_padding(GTK_MISC(pwPixmap), 8, 8);
        gtk_box_pack_start(GTK_BOX(pwHbox), pwPixmap, FALSE, FALSE, 0);
    }

    cbData = g_new0(CallbackStruct, 1);

    cbData->DialogFun = (dialog_func_ty) okFun;

    cbData->data = okFunData;
    g_object_set_data_full(G_OBJECT(pwDialog), "cbData", cbData, g_free);
    if (!(flags & DIALOG_FLAG_NORESPONSE))
        g_signal_connect(pwDialog, "response", G_CALLBACK(DialogResponse), cbData);

    if ((flags & DIALOG_FLAG_NOOK) == 0) {
        int OkButton = (flags & DIALOG_FLAG_MODAL && (flags & DIALOG_FLAG_CLOSEBUTTON) == 0);

        gtk_dialog_add_button(GTK_DIALOG(pwDialog), OkButton ? _("OK") : _("Close"),
                              OkButton ? GTK_RESPONSE_OK : GTK_RESPONSE_CLOSE);
        gtk_dialog_set_default_response(GTK_DIALOG(pwDialog), OkButton ? GTK_RESPONSE_OK : GTK_RESPONSE_CLOSE);

        if (!fQuestion)
            gtk_widget_add_accelerator(DialogArea(pwDialog, DA_OK), "clicked", pag, GDK_Escape, 0, 0);
    }

    if (fQuestion)
        gtk_dialog_add_button(GTK_DIALOG(pwDialog), _("Cancel"), GTK_RESPONSE_CANCEL);

    if (flags & DIALOG_FLAG_MODAL)
        gtk_window_set_modal(GTK_WINDOW(pwDialog), TRUE);

    g_signal_connect(pwDialog, "map-event", G_CALLBACK(dialog_mapped), 0);

    return pwDialog;
}
