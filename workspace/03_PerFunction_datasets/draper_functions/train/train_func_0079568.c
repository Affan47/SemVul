infd_directory_handle_subscribe_chat(InfdDirectory* directory,
                                     InfXmlConnection* connection,
                                     xmlNodePtr xml,
                                     GError** error)
{
  InfdDirectoryPrivate* priv;
  InfCommunicationGroup* group;
  const gchar* method;
  gchar* seq;
  xmlNodePtr reply_xml;

  priv = INFD_DIRECTORY_PRIVATE(directory);


  if(priv->chat_session == NULL)
  {
    g_set_error(
      error,
      inf_directory_error_quark(),
      INF_DIRECTORY_ERROR_CHAT_DISABLED,
      "%s",
      _("The chat is disabled")
    );

    return FALSE;
  }

  if(!infd_directory_make_seq(directory, connection, xml, &seq, error))
    return FALSE;

  g_object_get(
    G_OBJECT(priv->chat_session),
    "subscription-group", &group,
    NULL
  );

  method = inf_communication_group_get_method_for_connection(
    group,
    connection
  );


  g_assert(method != NULL);


  reply_xml = xmlNewNode(NULL, (const xmlChar*)"subscribe-chat");

  xmlNewProp(
    reply_xml,
    (const xmlChar*)"group",
    (const xmlChar*)inf_communication_group_get_name(group)
  );

  xmlNewProp(
    reply_xml,
    (const xmlChar*)"method",
    (const xmlChar*)method
  );

  g_object_unref(group);

  if(seq) inf_xml_util_set_attribute(reply_xml, "seq", seq);

  infd_directory_add_subreq_chat(directory, connection);

  inf_communication_group_send_message(
    INF_COMMUNICATION_GROUP(priv->group),
    connection,
    reply_xml
  );

  g_free(seq);
  return TRUE;
}
