select_child_cfg(private_child_create_t *this)
{
	peer_cfg_t *peer_cfg;
	child_cfg_t *child_cfg = NULL;;

	peer_cfg = this->ike_sa->get_peer_cfg(this->ike_sa);
	if (peer_cfg && this->tsi && this->tsr)
	{
		linked_list_t *listr, *listi, *tsr, *tsi;

		tsr = get_ts_if_nat_transport(this, TRUE, this->tsr);
		tsi = get_ts_if_nat_transport(this, FALSE, this->tsi);

		listr = get_dynamic_hosts(this->ike_sa, TRUE);
		listi = get_dynamic_hosts(this->ike_sa, FALSE);
		child_cfg = peer_cfg->select_child_cfg(peer_cfg,
											tsr ?: this->tsr, tsi ?: this->tsi,
											listr, listi);
		if ((tsi || tsr) && child_cfg &&
			child_cfg->get_mode(child_cfg) != MODE_TRANSPORT)
		{

			child_cfg->destroy(child_cfg);
			child_cfg = NULL;
		}
		if (!child_cfg && (tsi || tsr))
		{

			child_cfg = peer_cfg->select_child_cfg(peer_cfg,
											this->tsr, this->tsi, listr, listi);
		}
		listr->destroy(listr);
		listi->destroy(listi);
		DESTROY_OFFSET_IF(tsi, offsetof(traffic_selector_t, destroy));
		DESTROY_OFFSET_IF(tsr, offsetof(traffic_selector_t, destroy));
	}

	return child_cfg;
}
