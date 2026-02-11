vm_enter_vm_native(void *target, void *stack_ptr)
{
	if (vm_native_stack_is_full()) {
		struct vm_object *e = vm_alloc_stack_overflow_error();
		if (!e)
			error("failed to allocate exception");

		signal_exception(e);
		return -1;
	}

	struct vm_native_stack_entry *tr = new_vm_native_stack_entry();

	tr->stack_ptr = stack_ptr;
	tr->target = target;
	return 0;
}
