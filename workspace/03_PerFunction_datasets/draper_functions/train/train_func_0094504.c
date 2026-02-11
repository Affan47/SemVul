drawing_prompt_to_save(gpaint_drawing *drawing)
{
    gboolean cancel = FALSE;
    debug_fn();

    if (drawing->modified)
    {
        GtkWidget *dialog;
        gint result;
        dialog = gtk_message_dialog_new(
               GTK_WINDOW(drawing->top_level),
               GTK_DIALOG_MODAL,
               GTK_MESSAGE_WARNING,
               GTK_BUTTONS_NONE,
               _("Do you want to save the changes you made to \"%s\"?\nYour changes will be lost if you don't save them."),
               drawing->filename->str);
#ifdef GTK_STOCK_DISCARD
        gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_DISCARD,GTK_RESPONSE_NO);
#else
        gtk_dialog_add_button(GTK_DIALOG(dialog), _("Close _without Saving"), GTK_RESPONSE_NO);
#endif
        gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
        gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_SAVE, GTK_RESPONSE_YES);

        result = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(GTK_WIDGET(dialog));
        while (gtk_events_pending())
        {
           gtk_main_iteration();
        }

        switch (result)
        {
            case GTK_RESPONSE_YES:
                if (drawing_save(drawing))
                {
                    cancel = FALSE;
                }
                else
                {
                    cancel = TRUE;
                }
                break;
            case GTK_RESPONSE_CANCEL:
                cancel = TRUE;
                break;
         }
    }
    return cancel;
}
