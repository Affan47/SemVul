remove_from_widgets_hash (gpointer name, gpointer hash_widget, gpointer widget)
{
	if (hash_widget == widget)
		return TRUE;
	return FALSE;
}
