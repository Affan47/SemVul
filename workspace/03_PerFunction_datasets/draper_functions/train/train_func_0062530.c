current_imf(gpointer dialog)
{
	GtkWidget *im_window;
	GtkList *list;
	GtkListItem *item;
	struct image_file *imf = NULL;

	d3_printf("get current imf\n");

	im_window = gtk_object_get_data(GTK_OBJECT(dialog), "im_window");
	g_return_val_if_fail(im_window != NULL, NULL);
	list = gtk_object_get_data(GTK_OBJECT(dialog), "image_file_list");
	g_return_val_if_fail(list != NULL, NULL);

	if (list->selection == NULL)
		gtk_list_select_item(list, 0);

	if (list->selection != NULL) {
		item = list->selection->data;
		imf = gtk_object_get_data(GTK_OBJECT(item), "imf");
	}
	return imf;
}
