vmw_resource_list_unreference(struct vmw_sw_context *sw_context,
					  struct list_head *list)
{
	struct vmw_resource_val_node *val, *val_next;


	list_for_each_entry_safe(val, val_next, list, head) {
		list_del_init(&val->head);
		vmw_resource_unreference(&val->res);

		if (val->staged_bindings) {
			if (val->staged_bindings != sw_context->staged_bindings)
				vmw_binding_state_free(val->staged_bindings);
			else
				sw_context->staged_bindings_inuse = false;
			val->staged_bindings = NULL;
		}

		kfree(val);
	}
}
