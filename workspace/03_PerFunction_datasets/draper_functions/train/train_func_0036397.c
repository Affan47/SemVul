clean_up_nsps (NMDeviceWimax *self, gboolean notify)
{
	NMDeviceWimaxPrivate *priv;

	g_return_if_fail (NM_IS_DEVICE_WIMAX (self));

	priv = NM_DEVICE_WIMAX_GET_PRIVATE (self);

	if (priv->active_nsp) {
		g_object_unref (priv->active_nsp);
		priv->active_nsp = NULL;
	}

	if (priv->nsps) {
		while (priv->nsps->len) {
			NMWimaxNsp *nsp = NM_WIMAX_NSP (g_ptr_array_index (priv->nsps, 0));

			if (notify)
				g_signal_emit (self, signals[NSP_REMOVED], 0, nsp);
			g_ptr_array_remove (priv->nsps, nsp);
			g_object_unref (nsp);
		}
		g_ptr_array_free (priv->nsps, TRUE);
		priv->nsps = NULL;
	}
}
