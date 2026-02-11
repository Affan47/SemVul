gg_session_handle_login_ok(struct gg_session *gs, uint32_t type, const char *ptr, size_t len, struct gg_event *ge)
{
	gg_debug_session(gs, GG_DEBUG_MISC, "// gg_watch_fd() login succeded\n");
	ge->type = GG_EVENT_CONN_SUCCESS;
	gs->state = GG_STATE_CONNECTED;
	gs->check = GG_CHECK_READ;
	gs->timeout = -1;
	gs->status = (gs->initial_status) ? gs->initial_status : GG_STATUS_AVAIL;
#if 0
	free(gs->status_descr);
	gs->status_descr = gs->initial_descr;
#else
	free(gs->initial_descr);
#endif
	gs->initial_descr = NULL;

	return 0;
}
