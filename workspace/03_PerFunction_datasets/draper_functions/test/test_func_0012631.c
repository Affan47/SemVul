compositor_background_transparent(GF_Node *node)
{
	if (node && (gf_node_get_tag(node) == TAG_MPEG4_Background2D)) {
		Background2DStack *st;
		if (!((M_Background2D *)node)->isBound) return 1;

		st = (Background2DStack *) gf_node_get_private(node);
		if (st->txh.transparent) return 1;
		return 0;
	}

	return 1;
}
