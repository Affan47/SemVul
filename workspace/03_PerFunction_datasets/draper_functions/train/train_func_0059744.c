scan_thread_data (void *start_nursery, void *end_nursery, gboolean precise, GrayQueue *queue)
{
	SgenThreadInfo *info;

	scan_area_arg_start = start_nursery;
	scan_area_arg_end = end_nursery;

	FOREACH_THREAD (info) {
		if (info->skip) {
			SGEN_LOG (3, "Skipping dead thread %p, range: %p-%p, size: %td", info, info->stack_start, info->stack_end, (char*)info->stack_end - (char*)info->stack_start);
			continue;
		}
		if (info->gc_disabled) {
			SGEN_LOG (3, "GC disabled for thread %p, range: %p-%p, size: %td", info, info->stack_start, info->stack_end, (char*)info->stack_end - (char*)info->stack_start);
			continue;
		}
		if (mono_thread_info_run_state (info) != STATE_RUNNING) {
			SGEN_LOG (3, "Skipping non-running thread %p, range: %p-%p, size: %td (state %d)", info, info->stack_start, info->stack_end, (char*)info->stack_end - (char*)info->stack_start, mono_thread_info_run_state (info));
			continue;
		}
		SGEN_LOG (3, "Scanning thread %p, range: %p-%p, size: %td, pinned=%d", info, info->stack_start, info->stack_end, (char*)info->stack_end - (char*)info->stack_start, sgen_get_pinned_count ());
		if (gc_callbacks.thread_mark_func && !conservative_stack_mark) {
			UserCopyOrMarkData data = { NULL, queue };
			set_user_copy_or_mark_data (&data);
			gc_callbacks.thread_mark_func (info->runtime_data, info->stack_start, info->stack_end, precise);
			set_user_copy_or_mark_data (NULL);
		} else if (!precise) {
			if (!conservative_stack_mark) {
				fprintf (stderr, "Precise stack mark not supported - disabling.\n");
				conservative_stack_mark = TRUE;
			}
			conservatively_pin_objects_from (info->stack_start, info->stack_end, start_nursery, end_nursery, PIN_TYPE_STACK);
		}

		if (!precise) {
#ifdef USE_MONO_CTX
			conservatively_pin_objects_from ((void**)&info->ctx, (void**)&info->ctx + ARCH_NUM_REGS,
				start_nursery, end_nursery, PIN_TYPE_STACK);
#else
			conservatively_pin_objects_from ((void**)&info->regs, (void**)&info->regs + ARCH_NUM_REGS,
					start_nursery, end_nursery, PIN_TYPE_STACK);
#endif
		}
	} END_FOREACH_THREAD
}
