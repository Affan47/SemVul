DestroyBackground2D(GF_Node *node)
{
	Background2DStack *stack = (Background2DStack *) gf_node_get_private(node);

	PreDestroyBindable(node, stack->reg_stacks);
	gf_list_del(stack->reg_stacks);

	while (gf_list_count(stack->status_stack)) {
		BackgroundStatus *status = (BackgroundStatus *)gf_list_get(stack->status_stack, 0);
		gf_list_rem(stack->status_stack, 0);
		gf_free(status);
	}
	gf_list_del(stack->status_stack);

	drawable_del(stack->drawable);
	gf_sc_texture_destroy(&stack->txh);
#ifndef GPAC_DISABLE_3D
	if (stack->mesh) mesh_free(stack->mesh);
#endif
	gf_free(stack);
}
