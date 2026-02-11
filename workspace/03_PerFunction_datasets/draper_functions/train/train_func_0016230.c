is_perm_in_stack(uint32_t perm_value, uint32_t class_value, scope_stack_t * stack)
{
	if (stack == NULL) {
		return 0;
	}
	if (stack->type == 1) {
		avrule_decl_t *decl = stack->decl;
		if (is_perm_in_scope_index(perm_value, class_value, &decl->required)
		    || is_perm_in_scope_index(perm_value, class_value, &decl->declared)) {
			return 1;
		}
	} else {


	}


	return is_perm_in_stack(perm_value, class_value, stack->parent);
}
