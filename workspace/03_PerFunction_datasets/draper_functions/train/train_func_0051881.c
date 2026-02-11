jidToFileName(const XMPP::Jid &j)
{
	return ApplicationInfo::historyDir() + "/" + JIDUtil::encode(j.userHost()).toLower() + ".history";
}
