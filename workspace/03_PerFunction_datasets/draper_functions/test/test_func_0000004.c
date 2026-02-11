egg_asn1x_set_oid_as_quark (GNode *node,
                            GQuark oid)
{
	const gchar *str;

	g_return_val_if_fail (oid != 0, FALSE);

	str = g_quark_to_string (oid);
	g_return_val_if_fail (str != NULL, FALSE);

	return egg_asn1x_set_oid_as_string (node, str);
}
