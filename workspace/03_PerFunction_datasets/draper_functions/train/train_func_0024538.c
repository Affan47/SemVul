gth_file_list_get_preferred_height (GtkWidget *widget,
                		    int       *minimum_height,
                		    int       *natural_height)
{
	GthFileList *file_list = GTH_FILE_LIST (widget);
	const int    border = 1;

	gtk_widget_get_preferred_height (file_list->priv->view, minimum_height, natural_height);
	if (minimum_height)
		*minimum_height += border * 2;
	if (natural_height)
		*natural_height += border * 2;
}
