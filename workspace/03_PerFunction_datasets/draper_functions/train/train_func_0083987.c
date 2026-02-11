store_opened( store_t *ctx, void *aux )
{
	MVARS(aux)

	if (!ctx) {
		mvars->ret = mvars->skip = 1;
		mvars->state[t] = ST_CLOSED;
		sync_chans( mvars, E_OPEN );
		return;
	}
	mvars->ctx[t] = ctx;
	if (mvars->skip) {
		mvars->state[t] = ST_OPEN;
		sync_chans( mvars, E_OPEN );
		return;
	}
	if (!mvars->boxlist && mvars->chan->patterns && !ctx->listed)
		mvars->drv[t]->list( ctx, store_listed, AUX );
	else {
		mvars->state[t] = ST_OPEN;
		sync_chans( mvars, E_OPEN );
	}
}
