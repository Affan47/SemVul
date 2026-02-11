create_class_model(void)
{
	GtkListStore *model;
	GtkTreeIter iter;
	gint i;


	model = gtk_list_store_new(1, G_TYPE_STRING);
	for (i = 0; i < FILE_FORMAT_CLASSES; i++)
		{
		gtk_list_store_append(model, &iter);
		gtk_list_store_set(model, &iter, 0, _(format_class_list[i]), -1);
		}
	return GTK_TREE_MODEL (model);
}
