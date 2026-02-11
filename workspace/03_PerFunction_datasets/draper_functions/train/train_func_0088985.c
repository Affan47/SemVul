save_config_cb (void * hook_data, void * user_data)
{
    if (gtk_widget_get_visible ((GtkWidget *) user_data))
        save_position ((GtkWidget *) user_data);
}
