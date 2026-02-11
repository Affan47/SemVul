cd_device_set_model (CdDevice *device, const gchar *model)
{
	GString *tmp;
	CdDevicePrivate *priv = device->priv;


	tmp = g_string_new (model);


	if (priv->kind == CD_DEVICE_KIND_PRINTER)
		cd_device_string_remove_suffix (tmp->str, "Printer");
	if (priv->kind == CD_DEVICE_KIND_DISPLAY) {
		cd_device_string_remove_suffix (tmp->str, "Monitor");
		cd_device_string_remove_suffix (tmp->str, "Screen");
	}


	g_free (priv->model);
	priv->model = g_string_free (tmp, FALSE);
}
