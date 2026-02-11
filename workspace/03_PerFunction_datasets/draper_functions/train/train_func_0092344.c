slotGroupChatPresence (const XMPP::Jid & jid, const XMPP::Status & status)
{
  kDebug () << "Received groupchat presence for room " << jid.full() << status.isAvailable();

  if (status.isAvailable())
  {
    XMPP::Message message(jid);
    message.setType("ksirkgame");
    message.setId(QUuid::createUuid().toString().remove('{').remove('}').remove('-'));
    message.setBody(QString("Hello, ")+jid.full());
    m_jabberClient->sendMessage(message);
    m_presents.insert(jid.full());
  }
  else
  {
    m_presents.remove(jid.full());
  }
}
