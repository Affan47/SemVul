chap_timeout_timer(struct triton_timer_t *t)
{
	struct chap_auth_data *d = container_of(t, typeof(*d), timeout);

	if (conf_ppp_verbose)
		log_ppp_warn("chap-md5: timeout\n");

	if (++d->failure == conf_max_failure) {
		if (d->started)
			ap_session_terminate(&d->ppp->ses, TERM_USER_ERROR, 0);
		else
			ppp_auth_failed(d->ppp, NULL);
	} else
		chap_send_challenge(d, 0);
}
