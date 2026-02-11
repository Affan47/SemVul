file_new_dialog(gpaint_canvas *canvas)
{
    gpaint_new_drawing_dialog *dialog;
    char tmp[100];
    gint position = 0;
    GtkWidget *ok_button;
    GtkWidget *cancel_button;

    dialog = g_new0(gpaint_new_drawing_dialog, 1);
    g_assert(dialog);
    dialog->window = create_new_canvas_window();
    dialog->canvas = canvas;
    dialog->width_entry  = lookup_widget(dialog->window, "new_canvas_width_text_entry");
    dialog->height_entry = lookup_widget(dialog->window, "new_canvas_height_text_entry");
    sprintf(tmp, "%d", canvas->drawing->width);
    gtk_editable_insert_text(GTK_EDITABLE(dialog->width_entry), tmp, strlen(tmp), &position);
    position = 0;
    sprintf(tmp, "%d", canvas->drawing->height);
    gtk_editable_insert_text(GTK_EDITABLE(dialog->height_entry), tmp, strlen(tmp), &position);


    ok_button     = lookup_widget(dialog->window, "new_canvas_ok_button");
    cancel_button = lookup_widget(dialog->window, "new_canvas_cancel_button");
    gtk_object_set_user_data(GTK_OBJECT(ok_button), dialog);
    gtk_object_set_user_data(GTK_OBJECT(cancel_button), dialog);
    gtk_object_set_user_data(GTK_OBJECT(dialog->window), dialog);

    gtk_widget_show(dialog->window);
}
