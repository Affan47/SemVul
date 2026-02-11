start_wizard (NmaBtDevice *self,
              const gchar *path,
              NMDeviceType devtype)
{
	NmaBtDevicePrivate *priv = NMA_BT_DEVICE_GET_PRIVATE (self);

	if (devtype == NM_DEVICE_TYPE_UNKNOWN) {
		dun_error (self, __func__, NULL, _("unknown modem type."));
		return;
	}

	if (priv->wizard) {
		g_message ("%s: (%s) oops! not starting Wizard as one is already in progress", __func__, path);
		return;
	}

	g_message ("%s: (%s) starting the mobile wizard", __func__, path);

	g_source_remove (priv->dun_timeout_id);
	priv->dun_timeout_id = 0;


	priv->wizard = nma_mobile_wizard_new (priv->parent_window,
	                                      priv->window_group,
	                                      devtype,
	                                      FALSE,
	                                      wizard_done_cb,
	                                      self);
	nma_mobile_wizard_present (priv->wizard);
}
