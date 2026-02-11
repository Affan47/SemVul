anode_decode_sequence_or_set_of (GNode *node,
                                 Atlv *tlv)
{
	Atlv *ctlv;
	GNode *child, *other;
	gulong tag;
	gint i;


	child = node->children;
	g_return_val_if_fail (child, FALSE);

	for (ctlv = tlv->child, i = 0; ctlv != NULL; ctlv = ctlv->next, i++) {


		if (i == 0)
			tag = anode_calc_tag (child);
		else if (tag != G_MAXULONG && ctlv->tag != tag)
			return anode_failure (node, "invalid mismatched content");


		if (i == 0) {
			other = child;
		} else {
			other = anode_clone (child);
			g_node_append (node, other);
		}

		if (!anode_decode_one (other, ctlv))
			return FALSE;
	}

	return TRUE;
}
