be_pair_transfer(struct bufferevent *src, struct bufferevent *dst,
    int ignore_wm)
{
	size_t dst_size;
	size_t n;

	evbuffer_unfreeze(src->output, 1);
	evbuffer_unfreeze(dst->input, 0);

	if (dst->wm_read.high) {
		dst_size = evbuffer_get_length(dst->input);
		if (dst_size < dst->wm_read.high) {
			n = dst->wm_read.high - dst_size;
			evbuffer_remove_buffer(src->output, dst->input, n);
		} else {
			if (!ignore_wm)
				goto done;
			n = evbuffer_get_length(src->output);
			evbuffer_add_buffer(dst->input, src->output);
		}
	} else {
		n = evbuffer_get_length(src->output);
		evbuffer_add_buffer(dst->input, src->output);
	}

	if (n) {
		BEV_RESET_GENERIC_READ_TIMEOUT(dst);

		if (evbuffer_get_length(dst->output))
			BEV_RESET_GENERIC_WRITE_TIMEOUT(dst);
		else
			BEV_DEL_GENERIC_WRITE_TIMEOUT(dst);
	}

	bufferevent_trigger_nolock_(dst, EV_READ, 0);
	bufferevent_trigger_nolock_(src, EV_WRITE, 0);
done:
	evbuffer_freeze(src->output, 1);
	evbuffer_freeze(dst->input, 0);
}
