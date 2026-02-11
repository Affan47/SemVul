list_changed_stacks_add(struct changed_var_stack *list_changed_stacks,
	unsigned long vreg)
{
	struct changed_var_stack *changed;

	changed = alloc_changed_var_stack(vreg);
	if (!changed)
		return -ENOMEM;

	insert_list(changed, &list_changed_stacks);

	return 0;
}
