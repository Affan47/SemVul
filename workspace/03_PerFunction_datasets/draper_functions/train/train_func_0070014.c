event_get_with_epoll(const struct poll_ctx *ctx, unsigned idx)
{
	const struct epoll_event *ev = &ctx->ep_arr[idx];
	struct event event;

	g_assert(CTX_IS_LOCKED(ctx));

	event.fd = GPOINTER_TO_INT(ev->data.ptr);
	event.condition =
		((EPOLLIN | EPOLLPRI | EPOLLHUP) & ev->events ? INPUT_EVENT_R : 0)
		| (EPOLLOUT & ev->events ? INPUT_EVENT_W : 0)
		| (EPOLLERR & ev->events ? INPUT_EVENT_EXCEPTION : 0);
	event.data_available = 0;
	return event;
}
