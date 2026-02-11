compositor_init_layout(GF_Compositor *compositor, GF_Node *node)
{
	LayoutStack *stack;
	GF_SAFEALLOC(stack, LayoutStack);

	parent_node_setup((ParentNode2D*)stack);
	stack->lines = gf_list_new();
	gf_node_set_private(node, stack);
	gf_node_set_callback_function(node, TraverseLayout);
	stack->hdl.sensor = node;
	stack->hdl.IsEnabled = layout_is_enabled;
	stack->hdl.OnUserEvent = OnLayout;
}
