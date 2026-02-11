gamgi_gtk_dialog_message_create (char *title,
char *message, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
GtkWidget *dialog;
GtkWidget *vbox;
GtkWidget *hbox;
GtkWidget *button;
GtkWidget *label;

if (gamgi->message != NULL) return;

gamgi->message = dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (dialog), title);
gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_NONE);
gtk_container_set_border_width (GTK_CONTAINER (dialog), 5);
gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(window->window));
g_signal_connect (dialog, "delete_event",
G_CALLBACK (gamgi_gtk_dialog_delete), &gamgi->message);

vbox = gtk_vbox_new (TRUE, 0);
gtk_container_add (GTK_CONTAINER (dialog), vbox);
gtk_widget_show (vbox);

label = gtk_label_new (message);
gtk_misc_set_padding (GTK_MISC (label), 10, 10);
gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
gtk_widget_show (label);

hbox = gtk_hbox_new (TRUE, 0);
gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
gtk_widget_show (hbox);

button = gamgi_gtk_dialog_button_create ("Cancel", "red");
gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);
gtk_widget_set_size_request (button, GAMGI_GTK_BUTTON_WIDTH, -1);
gtk_widget_grab_focus (button);
gtk_widget_show (button);
g_signal_connect (button, "clicked",
G_CALLBACK (gamgi_gtk_dialog_remove), &gamgi->message);

gtk_widget_show (dialog);
gtk_grab_add (dialog);
}
