cli_event_time_nested_stop(cli_events_t *ctx, unsigned id, unsigned nestedid)
{
    struct timeval tv;
    struct cli_event *ev = get_event(ctx, id);
    struct cli_event *evnested = get_event(ctx, nestedid);
    if (!ev || !evnested)
	return;
    if (ev->type != ev_time || evnested->type != ev_time) {
	cli_event_error_str(ctx, "cli_event_time* must be called with ev_time type");
	return;
    }
    gettimeofday(&tv, NULL);
    ev->u.v_int += ((int64_t)tv.tv_sec * 1000000) + tv.tv_usec;
    ev->u.v_int -= evnested->u.v_int;
}
