nm_ap_set_freq (NMAccessPoint *ap,
                const guint32 freq)
{
	NMAccessPointPrivate *priv;

	g_return_if_fail (NM_IS_AP (ap));

	priv = NM_AP_GET_PRIVATE (ap);

	if (priv->freq != freq) {
		priv->freq = freq;
		g_object_notify (G_OBJECT (ap), NM_AP_FREQUENCY);
	}
}
