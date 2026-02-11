action_invert_selection_callback (GtkAction *action,
				  gpointer callback_data)
{
	g_assert (NAUTILUS_IS_VIEW (callback_data));

	nautilus_view_invert_selection (callback_data);
}
