inf_communication_joined_group_publisher_notify_status_cb(GObject* object,
                                                          GParamSpec* pspec,
                                                          gpointer user_data)
{
  InfXmlConnectionStatus status;
  g_object_get(G_OBJECT(object), "status", &status, NULL);

  if(status == INF_XML_CONNECTION_CLOSING ||
     status == INF_XML_CONNECTION_CLOSED)
  {

    inf_communication_joined_group_set_publisher(
      INF_COMMUNICATION_JOINED_GROUP(user_data),
      NULL
    );
  }
}
