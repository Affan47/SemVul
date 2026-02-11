nautilus_path_bar_clear_buttons (NautilusPathBar *path_bar)
{
        while (path_bar->priv->button_list != NULL) {
                gtk_container_remove (GTK_CONTAINER (path_bar), BUTTON_DATA (path_bar->priv->button_list->data)->button);
        }
        path_bar->priv->first_scrolled_button = NULL;
}
