static_init (gamgi_window *window)
{
GtkWidget *dialog = window->dialog0;
GtkWidget *notebook;
GtkWidget *button;
GtkWidget *combo_above, *combo_below, *combo;
GtkRequisition size;
int width, height;


combo_above = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_above");
gtk_widget_size_request (GTK_WIDGET (combo_above), &size);
width = size.width; height = size.height;

combo_below = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_below");
gtk_widget_size_request (GTK_WIDGET (combo_below), &size);
if (size.width > width) width = size.width;
if (size.height > height) height = size.height;

gtk_widget_set_size_request (combo_above, width, height);
gtk_widget_set_size_request (combo_below, width, height);


button = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "button_below");
gtk_button_clicked (GTK_BUTTON (button));

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_method");
gtk_combo_box_set_active (GTK_COMBO_BOX (combo), 0);


notebook = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "notebook");
gtk_widget_size_request (GTK_WIDGET (notebook), &size);
gtk_widget_set_size_request (notebook, size.width, size.height);

static_reset (window);
}
