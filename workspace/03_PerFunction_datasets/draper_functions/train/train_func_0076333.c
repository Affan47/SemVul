ast_channel_set_linkgroup(struct ast_channel *chan, struct ast_channel *peer)
{
	const char* linkedid=NULL;
	struct ast_channel *bridged;

	linkedid = oldest_linkedid(ast_channel_linkedid(chan), ast_channel_linkedid(peer));
	linkedid = oldest_linkedid(linkedid, ast_channel_uniqueid(chan));
	linkedid = oldest_linkedid(linkedid, ast_channel_uniqueid(peer));
	if (ast_channel_internal_bridged_channel(chan)) {
		bridged = ast_bridged_channel(chan);
		if (bridged && bridged != peer) {
			linkedid = oldest_linkedid(linkedid, ast_channel_linkedid(bridged));
			linkedid = oldest_linkedid(linkedid, ast_channel_uniqueid(bridged));
		}
	}
	if (ast_channel_internal_bridged_channel(peer)) {
		bridged = ast_bridged_channel(peer);
		if (bridged && bridged != chan) {
			linkedid = oldest_linkedid(linkedid, ast_channel_linkedid(bridged));
			linkedid = oldest_linkedid(linkedid, ast_channel_uniqueid(bridged));
		}
	}


	linkedid = ast_strdupa(linkedid);

	ast_channel_change_linkedid(chan, linkedid);
	ast_channel_change_linkedid(peer, linkedid);
	if (ast_channel_internal_bridged_channel(chan)) {
		bridged = ast_bridged_channel(chan);
		if (bridged && bridged != peer) {
			ast_channel_change_linkedid(bridged, linkedid);
		}
	}
	if (ast_channel_internal_bridged_channel(peer)) {
		bridged = ast_bridged_channel(peer);
		if (bridged && bridged != chan) {
			ast_channel_change_linkedid(bridged, linkedid);
		}
	}
}
