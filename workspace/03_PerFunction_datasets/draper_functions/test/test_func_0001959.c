event_set_mask_with_poll(struct poll_ctx *ctx, int fd,
	inputevt_cond_t old, inputevt_cond_t cur)
{
	struct pollfd *pfd;
	relay_list_t *rl;

	g_assert(CTX_IS_LOCKED(ctx));
	g_assert(is_valid_fd(fd));

	old &= INPUT_EVENT_RW;
	cur &= INPUT_EVENT_RW;

	rl = htable_lookup(ctx->ht, int_to_pointer(fd));
	g_assert(NULL != rl);
	g_assert(NULL != rl->sl);

	g_assert(rl->poll_idx < ctx->num_poll_idx);
	pfd = &ctx->pfd_arr[rl->poll_idx];
	g_assert(cast_to_fd(pfd->fd) == fd);

	if (old != cur) {
		pfd->revents = 0;
		if (cur) {
			pfd->events = 0
				| (INPUT_EVENT_R & cur ? (POLLIN | POLLPRI) : 0)
				| (INPUT_EVENT_W & cur ? POLLOUT : 0);
		} else {
			pfd->events = 0;
		}
	}
	return 0;
}
