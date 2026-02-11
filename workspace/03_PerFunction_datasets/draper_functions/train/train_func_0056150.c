__intro_device_added (NMAMobileWizard *self, NMDevice *device, gboolean select_it)
{
	GtkTreeIter iter;
	const char *desc = nma_utils_get_device_description (device);
	NMDeviceModemCapabilities caps;

	if (!NM_IS_DEVICE_MODEM (device))
		return FALSE;

	caps = nm_device_modem_get_current_capabilities (NM_DEVICE_MODEM (device));
	if (caps & NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS) {
		if (!desc)
			desc = _("Installed GSM device");
	} else if (caps & NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO) {
		if (!desc)
			desc = _("Installed CDMA device");
	} else
		return FALSE;

	gtk_tree_store_append (GTK_TREE_STORE (self->dev_store), &iter, NULL);
	gtk_tree_store_set (GTK_TREE_STORE (self->dev_store),
	                    &iter,
	                    INTRO_COL_NAME, desc,
	                    INTRO_COL_DEVICE, device,
	                    -1);


	if (select_it)
		gtk_combo_box_set_active_iter (GTK_COMBO_BOX (self->dev_combo), &iter);

	gtk_widget_set_sensitive (self->dev_combo, TRUE);
	return TRUE;
}
