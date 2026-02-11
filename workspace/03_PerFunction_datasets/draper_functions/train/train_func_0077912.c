svg_traverse_filter(GF_Node *node, void *rs, Bool is_destroy)
{
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	GF_FilterStack *st = gf_node_get_private(node);
	if (is_destroy) {
		drawable_del(st->drawable);
		if (st->data) gf_free(st->data);
		st->txh.data = NULL;
		gf_sc_texture_release(&st->txh);
		gf_sc_texture_destroy(&st->txh);
		gf_free(st);
		return;
	}

	if (tr_state->traversing_mode==TRAVERSE_DRAW_2D) {
		if (! tr_state->visual->DrawBitmap(tr_state->visual, tr_state, tr_state->ctx, NULL)) {
			visual_2d_texture_path(tr_state->visual, st->drawable->path, tr_state->ctx, tr_state);
		}
	}
}
