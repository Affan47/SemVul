anode_validate_boolean (GNode *node,
                        GBytes *value)
{
	const guchar *buf;
	gsize len;

	g_assert (value != NULL);
	buf = g_bytes_get_data (value, &len);


	if (len != 1)
		return anode_failure (node, "invalid length boolean");
	if (buf[0] != 0x00 && buf[0] != 0xFF)
		return anode_failure (node, "boolean must be true or false");
	return TRUE;
}
