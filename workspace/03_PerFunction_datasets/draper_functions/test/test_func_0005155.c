inf_chat_session_process_xml_sync(InfSession* session,
                                  InfXmlConnection* connection,
                                  xmlNodePtr xml,
                                  GError** error)
{
  if(strcmp((const char*)xml->name, "message") == 0)
  {
    return inf_chat_session_receive_message(
      INF_CHAT_SESSION(session),
      connection,
      xml,
      error
    );
  }
  else
  {
    g_assert(parent_class->process_xml_sync != NULL);
    return parent_class->process_xml_sync(session, connection, xml, error);
  }
}
