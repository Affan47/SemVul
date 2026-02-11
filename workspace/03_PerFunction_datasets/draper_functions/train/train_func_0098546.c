accesslog_op_bind( Operation *op, SlapReply *rs )
{
	slap_callback *sc;

	sc = op->o_tmpcalloc( 1, sizeof(slap_callback), op->o_tmpmemctx );
	sc->sc_response = accesslog_bind_resp;
	sc->sc_private = op->o_bd->bd_info;

	if ( op->o_callback ) {
		sc->sc_next = op->o_callback->sc_next;
		op->o_callback->sc_next = sc;
	} else {
		op->o_callback = sc;
	}
	return SLAP_CB_CONTINUE;
}
