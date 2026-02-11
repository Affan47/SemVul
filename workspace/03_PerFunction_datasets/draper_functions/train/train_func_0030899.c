amule_load_stats_tree(PHP_VALUE_NODE *result)
{
	if ( !result ) {
		return;
	}
	value_value_free(result);

	CECPacket req(EC_OP_GET_STATSTREE, EC_DETAIL_WEB);
	const CECPacket *response = CPhPLibContext::g_curr_context->WebServer()->webInterface->SendRecvMsg_v2(&req);
	if ( !response ) {
		return;
	}
	const CECTag *server_ver = response->GetTagByName(EC_TAG_SERVER_VERSION);
	const CECTag *user_nick = response->GetTagByName(EC_TAG_USER_NICK);
	if ( !server_ver || !user_nick ) {
		delete response;
		return;
	}
	CEC_StatTree_Node_Tag *stats_root = (CEC_StatTree_Node_Tag *)response->GetTagByName(EC_TAG_STATTREE_NODE);

	for (CECTag::const_iterator it = stats_root->begin(); it != stats_root->end(); it++) {
		CEC_StatTree_Node_Tag *tag = (CEC_StatTree_Node_Tag*) & *it;
		if (tag->GetTagName() == EC_TAG_STATTREE_NODE) {
			ecstats2php(tag, result);
		}
	}
}
