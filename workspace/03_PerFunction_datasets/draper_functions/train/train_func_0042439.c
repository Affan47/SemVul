slotJoinRoom()
{
  kDebug () << "Joining group chat...";
  XMPP::Jid roomJid(roomjid->text());
  QString groupchatHost = roomJid.domain();
  m_automaton->game()->setGroupchatHost(groupchatHost);
  QString groupchatRoom = roomJid.node();
  m_automaton->game()->setGroupchatRoom(groupchatRoom);
  QString groupchatNick = nickname->text();
  m_automaton->game()->setGroupchatNick(groupchatNick);
  QString groupchatPassword = roompassword->text();
  m_automaton->game()->setGroupchatPassword(groupchatPassword);
  KsirkSettings::setRoomJid(groupchatRoom+'@'+groupchatHost);
  KsirkSettings::setNickname(groupchatNick);
  KWallet::Wallet* wallet = KWallet::Wallet::openWallet("ksirk", 0);
  if (wallet == 0)
  {
    KsirkSettings::setRoomPassword(KStringHandler::obscure(groupchatPassword));
  }
  else
  {
    if (wallet->createFolder("jabber") && wallet->setFolder("jabber"))
    {
      wallet->writeEntry("roompassword", groupchatPassword.toUtf8());
    }
    delete wallet;
  }
  KsirkSettings::self()->writeConfig();


  if (groupchatPassword.isEmpty())
    m_automaton->game()->jabberClient()->joinGroupChat ( groupchatHost, groupchatRoom, groupchatNick);
  else
    m_automaton->game()->jabberClient()->joinGroupChat ( groupchatHost, groupchatRoom, groupchatNick, groupchatPassword);
}
