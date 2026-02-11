doConn(Connection *conn, RouterMsg *pMsg)
{
	GatewayInfo *pInfo = (GatewayInfo*)conn->getData();
	int pos = 0;
	while(pos + SID_LENGTH <= pMsg->slen){
		std::string sid(pMsg->data + pos, SID_LENGTH);
		LOG("new connection, sid=%s", sid.c_str());

		allSessions[sid] = conn;
		pInfo->sessions[sid] = 1;

		pos+= SID_LENGTH;
	}
}
