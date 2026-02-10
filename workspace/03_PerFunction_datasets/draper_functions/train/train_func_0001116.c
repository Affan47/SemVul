AddFriend(CFriend* toadd, bool notify)
{
	m_FriendList.push_back(toadd);
	SaveList();
	if (notify) {
		Notify_ChatUpdateFriend(toadd);
	}
}
