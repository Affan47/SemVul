PreDestroyBindable(GF_Node *bindable, GF_List *stack_list)
{
	Bool is_bound = Bindable_GetIsBound(bindable);
	Bindable_SetIsBound(bindable, 0);

	while (gf_list_count(stack_list)) {
		GF_Node *stack_top;
		GF_List *stack = (GF_List*)gf_list_get(stack_list, 0);
		gf_list_rem(stack_list, 0);
		gf_list_del_item(stack, bindable);
		if (is_bound) {
			stack_top = (GF_Node*)gf_list_get(stack, 0);
			if (stack_top) Bindable_SetSetBind(stack_top, 1);
		}
	}
}
