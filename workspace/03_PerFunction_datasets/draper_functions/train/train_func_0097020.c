compositor_init_untransform(GF_Compositor *compositor, GF_Node *node)
{
	Untransform tr;
	if (Untransform_GetNode(node, &tr)) {
		UntransformStack *stack;
		GF_SAFEALLOC(stack, UntransformStack);
		gf_node_set_private(node, stack);
		gf_node_set_callback_function(node, TraverseUntransform);
		stack->untr = tr;
		gf_node_proto_set_grouping(node);
	}
}
