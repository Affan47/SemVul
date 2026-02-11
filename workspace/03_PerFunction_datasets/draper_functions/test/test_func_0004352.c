nautilus_path_bar_get_preferred_width (GtkWidget *widget,
				       gint      *minimum,
				       gint      *natural)
{
	ButtonData *button_data;
	NautilusPathBar *path_bar;
	GList *list;
	gint child_height;
	gint height;
	gint child_min, child_nat;

	path_bar = NAUTILUS_PATH_BAR (widget);

	*minimum = *natural = 0;
	height = 0;

	for (list = path_bar->priv->button_list; list; list = list->next) {
		button_data = BUTTON_DATA (list->data);
		set_label_size_request (button_data);

		gtk_widget_get_preferred_width (button_data->button, &child_min, &child_nat);
		gtk_widget_get_preferred_height (button_data->button, &child_height, NULL);
		height = MAX (height, child_height);

		if (button_data->type == NORMAL_BUTTON) {

			child_min = MAX (child_min, child_height * 2);
			child_nat = MAX (child_min, child_height * 2);
		}

		*minimum = MAX (*minimum, child_min);
		*natural = MAX (*natural, child_nat);
	}


	path_bar->priv->slider_width = MIN (height * 2 / 3 + 5, height);

	if (path_bar->priv->button_list && path_bar->priv->button_list->next != NULL) {
		*minimum += (path_bar->priv->slider_width) * 2;
		*natural += (path_bar->priv->slider_width) * 2;
	}
}
