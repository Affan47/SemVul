rtw_free_uc_swdec_pending_queue23a(struct rtw_adapter *adapter)
{
	u32 cnt = 0;
	struct recv_frame *pending_frame;

	while ((pending_frame = rtw_alloc_recvframe23a(&adapter->recvpriv.uc_swdec_pending_queue))) {
		rtw_free_recvframe23a(pending_frame);
		DBG_8723A("%s: dequeue uc_swdec_pending_queue\n", __func__);
		cnt++;
	}

	return cnt;
}
