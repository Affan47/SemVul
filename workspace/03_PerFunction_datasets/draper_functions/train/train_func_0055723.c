fjes_txrx_stop_req_irq(struct fjes_adapter *adapter,
				   int src_epid)
{
	struct fjes_hw *hw = &adapter->hw;
	enum ep_partner_status status;

	status = fjes_hw_get_partner_ep_status(hw, src_epid);
	switch (status) {
	case EP_PARTNER_UNSHARE:
	case EP_PARTNER_COMPLETE:
	default:
		break;
	case EP_PARTNER_WAITING:
		if (src_epid < hw->my_epid) {
			hw->ep_shm_info[src_epid].tx.info->v1i.rx_status |=
				FJES_RX_STOP_REQ_DONE;

			clear_bit(src_epid, &hw->txrx_stop_req_bit);
			set_bit(src_epid, &adapter->unshare_watch_bitmask);

			if (!work_pending(&adapter->unshare_watch_task))
				queue_work(adapter->control_wq,
					   &adapter->unshare_watch_task);
		}
		break;
	case EP_PARTNER_SHARED:
		if (hw->ep_shm_info[src_epid].rx.info->v1i.rx_status &
		    FJES_RX_STOP_REQ_REQUEST) {
			set_bit(src_epid, &hw->epstop_req_bit);
			if (!work_pending(&hw->epstop_task))
				queue_work(adapter->control_wq,
					   &hw->epstop_task);
		}
		break;
	}
}
