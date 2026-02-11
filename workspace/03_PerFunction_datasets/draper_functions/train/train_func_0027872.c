compositor_init_svg_switch(GF_Compositor *compositor, GF_Node *node)
{
	s32 *selected_idx;
	GF_SAFEALLOC(selected_idx, u32);
	*selected_idx = -1;
	gf_node_set_private(node, selected_idx);
	gf_node_set_callback_function(node, svg_traverse_switch);
}
