bna_uninit(struct bna *bna)
{
	if (bna->mod_flags & BNA_MOD_F_INIT_DONE) {
		bna_mcam_mod_uninit(&bna->mcam_mod);
		bna_ucam_mod_uninit(&bna->ucam_mod);
		bna_rx_mod_uninit(&bna->rx_mod);
		bna_tx_mod_uninit(&bna->tx_mod);
		bna->mod_flags &= ~BNA_MOD_F_INIT_DONE;
	}

	bna_stats_mod_uninit(&bna->stats_mod);
	bna_ethport_uninit(&bna->ethport);
	bna_enet_uninit(&bna->enet);

	bna_ioceth_uninit(&bna->ioceth);

	bna->bnad = NULL;
}
