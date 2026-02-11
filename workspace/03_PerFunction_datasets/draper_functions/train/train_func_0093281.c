compositor_background2d_modified(GF_Node *node)
{
	M_Background2D *bck = (M_Background2D *)node;
	Background2DStack *st = (Background2DStack *) gf_node_get_private(node);
	if (!st) return;


	gf_node_dirty_set(node, 0, 1);


	if (st->txh.is_open) {
		if (! gf_sc_texture_check_url_change(&st->txh, &bck->url)) return;
		gf_sc_texture_stop(&st->txh);
		gf_sc_texture_play(&st->txh, &bck->url);
		return;
	}

	if (bck->url.count)
		gf_sc_texture_play(&st->txh, &bck->url);
	gf_sc_invalidate(st->txh.compositor, NULL);
}
