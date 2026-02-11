cli_event_fastdata(cli_events_t *ctx, unsigned id, const void *data, uint32_t len)
{
    struct cli_event *ev = get_event(ctx, id);
    if (!ev)
	return;
    if (ev->type != ev_data_fast) {
	cli_event_error_str(ctx, "cli_event_fastdata must be called with ev_data_fast");
	return;
    }
    ev->u.v_int = CrcUpdate(ev->u.v_int, data, len);
    ev->count += len;


}
