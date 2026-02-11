brasero_disc_add_ui (BraseroDisc *disc, GtkUIManager *manager, GtkWidget *message)
{
	BraseroDiscIface *iface;

	if (!disc)
		return 0;

	g_return_val_if_fail (BRASERO_IS_DISC (disc), 0);
	g_return_val_if_fail (GTK_IS_UI_MANAGER (manager), 0);

	iface = BRASERO_DISC_GET_IFACE (disc);
	if (iface->add_ui)
		return (* iface->add_ui) (disc, manager, message);

	return 0;
}
