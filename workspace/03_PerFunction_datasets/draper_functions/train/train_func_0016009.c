sync_boxes( store_t *ctx[], const char *names[], channel_conf_t *chan,
            void (*cb)( int sts, void *aux ), void *aux )
{
	sync_vars_t *svars;
	int t;

	svars = nfcalloc( sizeof(*svars) );
	svars->t[1] = 1;
	svars->ref_count = 1;
	svars->cb = cb;
	svars->aux = aux;
	svars->ctx[0] = ctx[0];
	svars->ctx[1] = ctx[1];
	svars->chan = chan;
	svars->uidval[0] = svars->uidval[1] = -1;
	svars->srecadd = &svars->srecs;

	for (t = 0; t < 2; t++) {
		ctx[t]->orig_name =
			(!names[t] || (ctx[t]->conf->map_inbox && !strcmp( ctx[t]->conf->map_inbox, names[t] ))) ?
				"INBOX" : names[t];
		if (!ctx[t]->conf->flat_delim) {
			ctx[t]->name = nfstrdup( ctx[t]->orig_name );
		} else if (map_name( ctx[t]->orig_name, &ctx[t]->name, 0, "/", ctx[t]->conf->flat_delim ) < 0) {
			error( "Error: canonical mailbox name '%s' contains flattened hierarchy delimiter\n", ctx[t]->name );
			svars->ret = SYNC_FAIL;
			sync_bail3( svars );
			return;
		}
		ctx[t]->uidvalidity = -1;
		set_bad_callback( ctx[t], store_bad, AUX );
		svars->drv[t] = ctx[t]->conf->driver;
	}


	sync_ref( svars );
	for (t = 0; t < 2; t++) {
		info( "Selecting %s %s...\n", str_ms[t], ctx[t]->orig_name );
		svars->drv[t]->select( ctx[t], (chan->ops[t] & OP_CREATE) != 0, box_selected, AUX );
		if (check_cancel( svars ))
			break;
	}
	sync_deref( svars );
}
