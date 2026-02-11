brasero_disc_get_boundaries (BraseroDisc *disc,
			     gint64 *start,
			     gint64 *end)
{
	BraseroDiscIface *iface;

	g_return_val_if_fail (BRASERO_IS_DISC (disc), FALSE);
	iface = BRASERO_DISC_GET_IFACE (disc);
	if (iface->get_boundaries)
		return (* iface->get_boundaries) (disc,
						  start,
						  end);

	return FALSE;
}
