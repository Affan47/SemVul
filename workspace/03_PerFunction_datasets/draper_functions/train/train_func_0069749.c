inf_communication_hosted_group_remove_member(InfCommunicationHostedGroup* grp,
                                             InfXmlConnection* connection)
{
  g_return_if_fail(INF_COMMUNICATION_IS_HOSTED_GROUP(grp));
  g_return_if_fail(INF_IS_XML_CONNECTION(connection));

  g_return_if_fail(
    inf_communication_group_is_member(
      INF_COMMUNICATION_GROUP(grp),
      connection
    )
  );

  _inf_communication_group_remove_member(
    INF_COMMUNICATION_GROUP(grp),
    connection
  );
}
