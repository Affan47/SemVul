cli_event_data(cli_events_t *ctx, unsigned id, const void *data, uint32_t len)
{
    struct cli_event *ev = get_event(ctx, id);
    if (!ev)
	return;
    if (ev->type != ev_data) {
	cli_event_error_str(ctx, "cli_event_string must be called with ev_data type");
	return;
    }
    switch (ev->multiple) {
	case multiple_last:
	    {
		void *v_data = cli_realloc2(ev->u.v_data, len);
		if (v_data) {
		    ev->u.v_data = v_data;
		    memcpy(v_data, data, len);
		    ev->count = len;
		} else {
		    cli_event_error_oom(ctx, len);
		}
		break;
	    }
	case multiple_concat:
	    {
		void *v_data = cli_realloc2(ev->u.v_data, ev->count + len);
		if (v_data) {
		    ev->u.v_data = v_data;
		    memcpy((char*)v_data + ev->count, data, len);
		    ev->count += len;
		} else {
		    cli_event_error_oom(ctx, ev->count + len);
		}
		break;
	    }
    }
}
