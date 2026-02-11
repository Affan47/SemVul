cli_event_debug_all(cli_events_t *ctx)
{
    unsigned i;
    for (i=0;i<ctx->max;i++) {
	if (ctx->events[i].count)
	    cli_event_debug(ctx, i);
    }
}
