egg_asn1x_set_null (GNode *node)
{
	g_return_if_fail (node != NULL);
	g_return_if_fail (anode_def_type (node) == EGG_ASN1X_NULL);


	anode_clr_value (node);
	anode_set_value (node, g_bytes_new_static ("", 0));
}
