bnad_netif_rx_schedule_poll(struct bnad *bnad, struct bna_ccb *ccb)
{
	struct bnad_rx_ctrl *rx_ctrl = (struct bnad_rx_ctrl *)(ccb->ctrl);
	struct napi_struct *napi = &rx_ctrl->napi;

	if (likely(napi_schedule_prep(napi))) {
		__napi_schedule(napi);
		rx_ctrl->rx_schedule++;
	}
}
