compute_frame_info (MonoInternalThread *thread, DebuggerTlsData *tls)
{
	ComputeFramesUserData user_data;
	GSList *tmp;
	int i, findex, new_frame_count;
	StackFrame **new_frames, *f;
	MonoUnwindOptions opts = (MonoUnwindOptions)(MONO_UNWIND_DEFAULT | MONO_UNWIND_REG_LOCATIONS);


	if (tls->frames && tls->frames_up_to_date)
		return;

	DEBUG_PRINTF (1, "Frames for %p(tid=%lx):\n", thread, (glong)thread->tid);

	user_data.tls = tls;
	user_data.frames = NULL;
	if (tls->terminated) {
		tls->frame_count = 0;
		return;
	} if (!tls->really_suspended && tls->async_state.valid) {

		process_frame (&tls->async_last_frame, NULL, &user_data);
		mono_walk_stack_with_state (process_frame, &tls->async_state, opts, &user_data);
	} else if (tls->filter_state.valid) {


		if (tls->context.valid)
			mono_walk_stack_with_state (process_filter_frame, &tls->context, opts, &user_data);


		mono_walk_stack_with_state (process_frame, &tls->filter_state, opts, &user_data);
	} else if (tls->context.valid) {
		mono_walk_stack_with_state (process_frame, &tls->context, opts, &user_data);
	} else {

		tls->frame_count = 0;
		return;
	}

	new_frame_count = g_slist_length (user_data.frames);
	new_frames = g_new0 (StackFrame*, new_frame_count);
	findex = 0;
	for (tmp = user_data.frames; tmp; tmp = tmp->next) {
		f = (StackFrame *)tmp->data;


		for (i = 0; i < tls->frame_count; ++i) {
			if (MONO_CONTEXT_GET_SP (&tls->frames [i]->ctx) == MONO_CONTEXT_GET_SP (&f->ctx)) {
				f->id = tls->frames [i]->id;
				break;
			}
		}

		if (i >= tls->frame_count)
			f->id = InterlockedIncrement (&frame_id);

		new_frames [findex ++] = f;
	}

	g_slist_free (user_data.frames);

	invalidate_frames (tls);

	tls->frames = new_frames;
	tls->frame_count = new_frame_count;
	tls->frames_up_to_date = TRUE;
}
