recv_func_prehandle(struct rtw_adapter *padapter,
			       struct recv_frame *rframe)
{
	int ret;


	ret = validate_recv_frame(padapter, rframe);
	if (ret != _SUCCESS) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
			 "recv_func: validate_recv_frame fail! drop pkt\n");
		rtw_free_recvframe23a(rframe);
		goto exit;
	}

exit:
	return ret;
}
