cooler_temp_cb( GtkWidget *widget, gpointer data )
{
	GtkWidget *main_window = gtk_object_get_data(GTK_OBJECT(data), "image_window");
	struct camera_t *camera = camera_find(main_window, CAMERA_MAIN);
	float temp_set;
	if(! camera) {
		err_printf("no camera connected\n");
		return;
	}
	temp_set = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(widget));
	camera_set_temperature(camera, temp_set);
}
