alloc_vrrp_unicast_peer(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	struct sockaddr_storage *peer = NULL;
	int ret;

	if (LIST_ISEMPTY(vrrp->unicast_peer))
		vrrp->unicast_peer = alloc_list(free_unicast_peer, dump_unicast_peer);


	peer = (struct sockaddr_storage *) MALLOC(sizeof(struct sockaddr_storage));
	ret = inet_stosockaddr(vector_slot(strvec, 0), 0, peer);
	if (ret < 0) {
		log_message(LOG_ERR, "Configuration error: VRRP instance[%s] malformed unicast"
				     " peer address[%s]. Skipping..."
				   , vrrp->iname, vector_slot(strvec, 0));
		FREE(peer);
		return;
	}

	if (peer->ss_family != vrrp->family) {
		log_message(LOG_ERR, "Configuration error: VRRP instance[%s] and unicast peer address"
				     "[%s] MUST be of the same family !!! Skipping..."
				   , vrrp->iname, vector_slot(strvec, 0));
		FREE(peer);
		return;
	}

	list_add(vrrp->unicast_peer, peer);
}
