vrrp_state_backup(vrrp_t * vrrp, char *buf, int buflen)
{
	vrrphdr_t *hd;
	uint32_t saddr;
	int ret = 0, proto;


	hd = vrrp_get_header(vrrp->family, buf, &proto, &saddr);
	ret = vrrp_check_packet(vrrp, buf, buflen);

	if (ret == VRRP_PACKET_KO || ret == VRRP_PACKET_NULL) {
		log_message(LOG_INFO, "VRRP_Instance(%s) ignoring received advertisment..."
			            ,  vrrp->iname);
		vrrp->ms_down_timer = 3 * vrrp->adver_int + VRRP_TIMER_SKEW(vrrp);
	} else if (hd->priority == 0) {
		vrrp->ms_down_timer = VRRP_TIMER_SKEW(vrrp);
	} else if (vrrp->nopreempt || hd->priority >= vrrp->effective_priority ||
		   timer_cmp(vrrp->preempt_time, timer_now()) > 0) {
		vrrp->ms_down_timer = 3 * vrrp->adver_int + VRRP_TIMER_SKEW(vrrp);
	} else if (hd->priority < vrrp->effective_priority) {
		log_message(LOG_INFO, "VRRP_Instance(%s) forcing a new MASTER election"
				    , vrrp->iname);
		vrrp->wantstate = VRRP_STATE_GOTO_MASTER;
		vrrp_send_adv(vrrp, vrrp->effective_priority);
	}
}
