compositor_init_offscreen_group(GF_Compositor *compositor, GF_Node *node)
{
	OffscreenGroup og;
	if (OffscreenGroup_GetNode(node, &og)) {
		OffscreenGroupStack *stack;
		GF_SAFEALLOC(stack, OffscreenGroupStack);
		gf_node_set_private(node, stack);
		gf_node_set_callback_function(node, TraverseOffscreenGroup);
		stack->og = og;
		if (og.offscreen) stack->flags |= GROUP_IS_CACHED;
		gf_node_proto_set_grouping(node);
	}
}
