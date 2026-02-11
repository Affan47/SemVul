fc_fabric_logoff(struct fc_lport *lport)
{
	lport->tt.disc_stop_final(lport);
	mutex_lock(&lport->lp_mutex);
	if (lport->dns_rdata)
		lport->tt.rport_logoff(lport->dns_rdata);
	mutex_unlock(&lport->lp_mutex);
	lport->tt.rport_flush_queue();
	mutex_lock(&lport->lp_mutex);
	fc_lport_enter_logo(lport);
	mutex_unlock(&lport->lp_mutex);
	cancel_delayed_work_sync(&lport->retry_work);
	return 0;
}
