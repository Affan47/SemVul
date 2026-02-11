egg_asn1x_count (GNode *node)
{
	guint result = 0;
	GNode *child;
	gint type;

	g_return_val_if_fail (node, 0);

	type = anode_def_type (node);
	if (type != EGG_ASN1X_SEQUENCE_OF && type != EGG_ASN1X_SET_OF) {
		g_warning ("node passed to egg_asn1x_count was not a sequence of or set of");
		return 0;
	}

	for (child = node->children; child; child = child->next) {
		if (egg_asn1x_have (child))
			++result;
	}

	return result;
}
