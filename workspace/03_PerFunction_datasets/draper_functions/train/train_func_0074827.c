chap_finish(struct ppp_t *ppp, struct auth_data_t *auth)
{
	struct chap_auth_data *d = container_of(auth, typeof(*d), auth);

	if (d->timeout.tpd)
		triton_timer_del(&d->timeout);

	if (d->interval.tpd)
		triton_timer_del(&d->interval);

	ppp_unregister_handler(ppp,&d->h);

	return 0;
}
