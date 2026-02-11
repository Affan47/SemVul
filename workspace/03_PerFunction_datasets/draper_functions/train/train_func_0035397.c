bluetooth_chooser_start_discovery (BluetoothChooser *self)
{
	BluetoothChooserPrivate *priv = BLUETOOTH_CHOOSER_GET_PRIVATE(self);

	g_return_if_fail (priv->show_searching);

	g_object_set (G_OBJECT (priv->client), "default-adapter-discovering", TRUE, NULL);
	set_search_label (self, TRUE);
	priv->disco_rq = TRUE;
}
