filter_category_changed_cb (GtkComboBox *widget, gpointer data)
{
	BluetoothFilterWidget *self = BLUETOOTH_FILTER_WIDGET (data);
	BluetoothFilterWidgetPrivate *priv = BLUETOOTH_FILTER_WIDGET_GET_PRIVATE(self);

	priv->device_category_filter = gtk_combo_box_get_active (GTK_COMBO_BOX(priv->device_category));
	if (priv->filter)
		gtk_tree_model_filter_refilter (GTK_TREE_MODEL_FILTER (priv->filter));
	g_object_notify (G_OBJECT(self), "device-category-filter");
}
