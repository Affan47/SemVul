spank_stack_destroy (struct spank_stack *stack)
{
	if (stack->plugin_list)
		list_destroy (stack->plugin_list);
	if (stack->option_cache)
		list_destroy (stack->option_cache);
	xfree (stack->plugin_path);
	xfree (stack);
}
