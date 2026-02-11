slotGroupChatJoined (const XMPP::Jid & jid)
{
  kDebug () << "Joined groupchat " << jid.full ();


  XMPP::Message message(QString(m_groupchatRoom+'@'+m_groupchatHost));
  message.setType("groupchat");
  message.setId(QUuid::createUuid().toString().remove('{').remove('}').remove('-'));
  message.setBody("Hello, I'm a KsirK Game");
  m_jabberClient->sendMessage(message);

  askForJabberGames();
}
