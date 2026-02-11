bna_enet_disable(struct bna_enet *enet, enum bna_cleanup_type type,
		 void (*cbfn)(void *))
{
	if (type == BNA_SOFT_CLEANUP) {
		(*cbfn)(enet->bna->bnad);
		return;
	}

	enet->stop_cbfn = cbfn;
	enet->stop_cbarg = enet->bna->bnad;

	enet->flags &= ~BNA_ENET_F_ENABLED;

	bfa_fsm_send_event(enet, ENET_E_STOP);
}
