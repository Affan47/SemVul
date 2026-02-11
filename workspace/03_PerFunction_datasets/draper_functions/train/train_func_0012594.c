l2d_CheckBindables(GF_Node *n, GF_TraverseState *tr_state, Bool force_traverse)
{
	GF_Node *btop;
	M_Layer2D *l2d;
	l2d = (M_Layer2D *)n;
	if (force_traverse) gf_node_traverse(l2d->background, tr_state);
	btop = (GF_Node*)gf_list_get(tr_state->backgrounds, 0);
	if (btop != l2d->background) {
		gf_node_unregister(l2d->background, n);
		gf_node_register(btop, n);
		l2d->background = btop;
		gf_node_event_out_str(n, "background");
	}
	if (force_traverse) gf_node_traverse(l2d->viewport, tr_state);
	btop = (GF_Node*)gf_list_get(tr_state->viewpoints, 0);
	if (btop != l2d->viewport) {
		gf_node_unregister(l2d->viewport, n);
		gf_node_register(btop, n);
		l2d->viewport = btop;
		gf_node_event_out_str(n, "viewport");
	}
}
