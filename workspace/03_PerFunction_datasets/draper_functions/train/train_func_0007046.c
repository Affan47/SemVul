Add_EC_Client(CECServerSocket *sock)
{
	ECUpdateMsgSource **notifier_array = new ECUpdateMsgSource *[EC_STATUS_LAST_PRIO];
	notifier_array[EC_STATUS] = new ECStatusMsgSource();
	notifier_array[EC_SEARCH] = new ECSearchMsgSource();
	notifier_array[EC_PARTFILE] = new ECPartFileMsgSource();
	notifier_array[EC_CLIENT] = new ECClientMsgSource();
	notifier_array[EC_KNOWN] = new ECKnownFileMsgSource();

	m_msg_source[sock] = notifier_array;
}
