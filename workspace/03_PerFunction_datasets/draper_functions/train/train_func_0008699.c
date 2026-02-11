gal_a11y_e_table_click_to_add_new (GObject *widget)
{
	GalA11yETableClickToAdd *a11y;
	ETableClickToAdd * etcta;
	GalA11yETableClickToAddPrivate *priv;

	g_return_val_if_fail (widget != NULL, NULL);

	a11y = g_object_new (gal_a11y_e_table_click_to_add_get_type (), NULL);
	priv = GET_PRIVATE (a11y);

	etcta = E_TABLE_CLICK_TO_ADD (widget);

	atk_object_initialize (ATK_OBJECT (a11y), etcta);

	priv->rect = etcta->rect;
	priv->row = etcta->row;

	g_signal_connect_after (
		widget, "event",
		G_CALLBACK (etcta_event), a11y);

	g_signal_connect (
		etcta->selection, "cursor_changed",
		G_CALLBACK (etcta_selection_cursor_changed), a11y);

	return ATK_OBJECT (a11y);
}
