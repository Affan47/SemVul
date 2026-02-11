ipoe_serv_add_disc(struct ipoe_serv *serv, struct dhcpv4_packet *pack, int offer_delay)
{
	struct disc_item *d = mempool_alloc(disc_item_pool);

	if (!d)
		return;

	__sync_add_and_fetch(&stat_delayed_offer, 1);

	dhcpv4_packet_ref(pack);
	d->pack = pack;
	clock_gettime(CLOCK_MONOTONIC, &d->ts);
	list_add_tail(&d->entry, &serv->disc_list);

	if (!serv->disc_timer.tpd) {
		serv->disc_timer.expire_tv.tv_sec = offer_delay / 1000;
		serv->disc_timer.expire_tv.tv_usec = (offer_delay % 1000) * 1000;
		triton_timer_add(&serv->ctx, &serv->disc_timer, 0);
	}
}
