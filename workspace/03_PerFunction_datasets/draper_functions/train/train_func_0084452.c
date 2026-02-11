egg_asn1x_get_value_raw (GNode *node)
{
	GBytes *raw;

	g_return_val_if_fail (node != NULL, NULL);
	raw = anode_get_value (node);
	if (raw != NULL)
		g_bytes_ref (raw);
	return raw;
}
