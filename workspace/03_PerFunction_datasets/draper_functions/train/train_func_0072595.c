bna_ioceth_sm_enet_stop_wait_entry(struct bna_ioceth *ioceth)
{
	bna_stats_mod_stop(&ioceth->bna->stats_mod);
	bna_enet_stop(&ioceth->bna->enet);
}
