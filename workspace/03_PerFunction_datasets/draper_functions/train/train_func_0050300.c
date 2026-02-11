inf_adopted_session_record_add_user_cb(InfUserTable* user_table,
                                       InfUser* user,
                                       gpointer user_data)
{
  InfAdoptedSessionRecord* record;
  InfAdoptedSessionRecordPrivate* priv;
  xmlNodePtr xml;
  int result;

  record = INF_ADOPTED_SESSION_RECORD(user_data);
  priv = INF_ADOPTED_SESSION_RECORD_PRIVATE(record);

  inf_adopted_session_record_user_joined(record, INF_ADOPTED_USER(user));

  result = xmlTextWriterWriteString(priv->writer, (const xmlChar*)"\n  ");
  if(result < 0) inf_adopted_session_record_handle_xml_error(record);

  xml = xmlNewNode(NULL, (const xmlChar*)"user");
  inf_session_user_to_xml(INF_SESSION(priv->session), user, xml);
  inf_adopted_session_record_write_node(record, xml);
  xmlFreeNode(xml);

  result = xmlTextWriterFlush(priv->writer);
  if(result < 0) inf_adopted_session_record_handle_xml_error(record);
  fflush(priv->file);
}
