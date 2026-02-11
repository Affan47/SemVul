compositor_init_lineprops(GF_Compositor *compositor, GF_Node *node)
{
	LinePropStack *st;
	GF_SAFEALLOC(st, LinePropStack);
	st->compositor = compositor;
	st->last_mod_time = 0;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, DestroyLineProps);
}
