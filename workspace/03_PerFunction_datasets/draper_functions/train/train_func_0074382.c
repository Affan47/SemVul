peer_destructor(void *obj)
{
	struct iax2_peer *peer = obj;
	int callno = peer->callno;

	ast_free_acl_list(peer->acl);

	if (callno > 0) {
		ast_mutex_lock(&iaxsl[callno]);
		iax2_destroy(callno);
		ast_mutex_unlock(&iaxsl[callno]);
	}

	register_peer_exten(peer, 0);

	if (peer->dnsmgr)
		ast_dnsmgr_release(peer->dnsmgr);

	if (peer->mwi_event_sub)
		ast_event_unsubscribe(peer->mwi_event_sub);

	ast_string_field_free_memory(peer);
}
