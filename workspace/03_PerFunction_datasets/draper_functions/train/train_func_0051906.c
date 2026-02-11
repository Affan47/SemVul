reload_icons (NautilusPathBar *path_bar)
{
        GList *list;

        for (list = path_bar->priv->button_list; list; list = list->next) {
                ButtonData *button_data;

                button_data = BUTTON_DATA (list->data);
		if (button_data->type != NORMAL_BUTTON || button_data->is_root) {
                	nautilus_path_bar_update_button_appearance (button_data);
		}

        }
}
