vrrp_state_goto_master(vrrp_t * vrrp)
{


	if (vrrp->sync && !vrrp_sync_goto_master(vrrp)) {


		vrrp->quick_sync = 1;
		return;
	}

	vrrp_send_adv(vrrp, vrrp->effective_priority);

	vrrp->state = VRRP_STATE_MAST;
	log_message(LOG_INFO, "VRRP_Instance(%s) Transition to MASTER STATE"
			    , vrrp->iname);
}
