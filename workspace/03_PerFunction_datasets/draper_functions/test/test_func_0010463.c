recv_indicatepkt_reorder(struct rtw_adapter *padapter,
			     struct recv_frame *prframe)
{
	int retval = _SUCCESS;
	struct rx_pkt_attrib *pattrib;
	struct recv_reorder_ctrl *preorder_ctrl;
	struct rtw_queue *ppending_recvframe_queue;

	pattrib = &prframe->attrib;
	preorder_ctrl = prframe->preorder_ctrl;
	ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;

	if (!pattrib->amsdu) {

		wlanhdr_to_ethhdr(prframe);

		if ((pattrib->qos!= 1) || (pattrib->eth_type == ETH_P_ARP) ||
		    (pattrib->ack_policy != 0)) {
			if ((padapter->bDriverStopped == false) &&
			    (padapter->bSurpriseRemoved == false)) {
				RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_,
					 "@@@@  recv_indicatepkt_reorder -recv_func recv_indicatepkt\n");

				rtw_recv_indicatepkt23a(padapter, prframe);
				return _SUCCESS;
			}

			return _FAIL;
		}

		if (preorder_ctrl->enable == false) {

			preorder_ctrl->indicate_seq = pattrib->seq_num;
			rtw_recv_indicatepkt23a(padapter, prframe);

			preorder_ctrl->indicate_seq =
				(preorder_ctrl->indicate_seq + 1) % 4096;
			return _SUCCESS;
		}
	} else {

		if (preorder_ctrl->enable == false) {
			preorder_ctrl->indicate_seq = pattrib->seq_num;
			retval = amsdu_to_msdu(padapter, prframe);

			preorder_ctrl->indicate_seq =
				(preorder_ctrl->indicate_seq + 1) % 4096;
			return retval;
		}
	}

	spin_lock_bh(&ppending_recvframe_queue->lock);

	RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_,
		 "recv_indicatepkt_reorder: indicate =%d seq =%d\n",
		 preorder_ctrl->indicate_seq, pattrib->seq_num);


	if (!check_indicate_seq(preorder_ctrl, pattrib->seq_num)) {
		goto _err_exit;
	}


	if (!enqueue_reorder_recvframe23a(preorder_ctrl, prframe)) {
		goto _err_exit;
	}


	if (recv_indicatepkts_in_order(padapter, preorder_ctrl, false) == true) {
		mod_timer(&preorder_ctrl->reordering_ctrl_timer,
			  jiffies + msecs_to_jiffies(REORDER_WAIT_TIME));
		spin_unlock_bh(&ppending_recvframe_queue->lock);
	} else {
		spin_unlock_bh(&ppending_recvframe_queue->lock);
		del_timer_sync(&preorder_ctrl->reordering_ctrl_timer);
	}
	return _SUCCESS;

_err_exit:

	spin_unlock_bh(&ppending_recvframe_queue->lock);
	return _FAIL;
}
