stacktrace_auto_tune(void)
{
	void *stack[STACKTRACE_DEPTH_MAX];
	size_t count;
	size_t i;

	count = stacktrace_safe_unwind(stack, G_N_ELEMENTS(stack), 0);


	for (i = 0; i < count; i++) {
		size_t d = ptr_diff(stack[i], func_to_pointer(stacktrace_auto_tune));

		if (size_is_non_negative(d) && d < 72)
			break;
	}


	if (count == i) {
		s_warning("could not auto-tune stacktrace offsets, using defaults");
		stack_auto_offset = 1;
	} else {
		stack_auto_offset = i;
	}
}
