callback_options_destroy (GtkWidget *widget, gpointer data)
{
  if (((struct s_options_data *) data) != NULL)
    free (((struct s_options_data *) data));
}
