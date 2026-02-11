dpd_check_event(void *v_sa)
{
	struct sa	*isakmp_sa = v_sa;
	struct sa	*sa;

	isakmp_sa->dpd_event = 0;

	if (++isakmp_sa->dpd_failcount < DPD_RETRANS_MAX) {
		LOG_DBG((LOG_MESSAGE, 10, "dpd_check_event: "
		    "peer not responding, retry %u of %u",
		    isakmp_sa->dpd_failcount, DPD_RETRANS_MAX));
		message_send_dpd_notify(isakmp_sa,
		    ISAKMP_NOTIFY_STATUS_DPD_R_U_THERE, isakmp_sa->dpd_seq);
		dpd_timer_reset(isakmp_sa, 0, DPD_TIMER_CHECK);
		return;
	}


	LOG_DBG((LOG_MESSAGE, 10, "dpd_check_event: peer is dead, "
	    "deleting all SAs connected to SA %p", isakmp_sa));
	while ((sa = sa_find(dpd_find_sa, isakmp_sa)) != 0) {
		LOG_DBG((LOG_MESSAGE, 30, "dpd_check_event: deleting SA %p",
		    sa));
		sa_delete(sa, 0);
	}
	LOG_DBG((LOG_MESSAGE, 30, "dpd_check_event: deleting ISAKMP SA %p",
	    isakmp_sa));
	sa_delete(isakmp_sa, 0);
}
