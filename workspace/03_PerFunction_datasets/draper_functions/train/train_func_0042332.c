cg_window_fetch_boolean (CgWindow *window,
                         const gchar *id)
{
	GtkWidget *widget;
	CgWindowPrivate *priv;

	priv = CG_WINDOW_PRIVATE (window);
	widget = GTK_WIDGET (gtk_builder_get_object (priv->bxml, id));

	g_return_val_if_fail (widget != NULL, FALSE);

	if (GTK_IS_TOGGLE_BUTTON (widget))
		return gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget));
	else
		return FALSE;
}
