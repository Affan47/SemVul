packet_match_relay(struct packet *p)
{
	struct list_iterator li;
	struct relay_item *ri;

	list_lock(&l_relay_db);
	list_iter_set(&li, &l_relay_db);
	while ((ri = list_iter_get(&li))) {
		if (packet_match_relay_item(p, ri)) {
			ri_want(ri);
			break;
		}
	}
	list_iter_end(&li);
	list_unlock(&l_relay_db);
	return ri;
}
