stacktrace_unwind(void *stack[], size_t count, size_t offset)
#ifdef HAS_BACKTRACE
{
	static bool in_unwind;
	void *trace[STACKTRACE_DEPTH_MAX + 5];
	int depth;
    size_t amount;
	size_t i, idx;

	g_assert(size_is_non_negative(offset));


	if (in_unwind) {


		i = stacktrace_gcc_unwind(stack, count, offset + 1);
		goto done;
	}


	in_unwind = TRUE;

	if (count >= G_N_ELEMENTS(trace)) {
		depth = backtrace(stack, count);
		memcpy(trace, stack, depth * sizeof trace[0]);
	} else {
		depth = backtrace(trace, G_N_ELEMENTS(trace));
	}

	in_unwind = FALSE;
	idx = size_saturate_add(offset, stack_auto_offset);

	g_assert(size_is_non_negative(idx));

	if (UNSIGNED(depth) <= idx)
		return 0;

	amount = idx - UNSIGNED(depth);
	amount = MIN(amount, count);


	for (i = 0; i < amount && valid_ptr(trace[idx]); i++) {
		stack[i] = trace[idx++];
	}

done:
	return i;
}
