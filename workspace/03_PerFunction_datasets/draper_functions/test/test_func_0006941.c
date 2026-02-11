intel_pt_interrupt(void)
{
	struct pt *pt = this_cpu_ptr(&pt_ctx);
	struct pt_buffer *buf;
	struct perf_event *event = pt->handle.event;


	if (!ACCESS_ONCE(pt->handle_nmi))
		return;

	pt_config_start(false);

	if (!event)
		return;

	buf = perf_get_aux(&pt->handle);
	if (!buf)
		return;

	pt_read_offset(buf);

	pt_handle_status(pt);

	pt_update_head(pt);

	perf_aux_output_end(&pt->handle, local_xchg(&buf->data_size, 0),
			    local_xchg(&buf->lost, 0));

	if (!event->hw.state) {
		int ret;

		buf = perf_aux_output_begin(&pt->handle, event);
		if (!buf) {
			event->hw.state = PERF_HES_STOPPED;
			return;
		}

		pt_buffer_reset_offsets(buf, pt->handle.head);

		ret = pt_buffer_reset_markers(buf, &pt->handle);
		if (ret) {
			perf_aux_output_end(&pt->handle, 0, true);
			return;
		}

		pt_config_buffer(buf->cur->table, buf->cur_idx,
				 buf->output_off);
		pt_config(event);
	}
}
