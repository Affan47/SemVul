compositor_init_fog(GF_Compositor *compositor, GF_Node *node)
{
	ViewStack *st;
	GF_SAFEALLOC(st, ViewStack);

	st->reg_stacks = gf_list_new();
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, TraverseFog);
	((M_Fog*)node)->on_set_bind = fog_set_bind;
}
