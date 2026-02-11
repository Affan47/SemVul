inf_communication_hosted_group_finalize(GObject* object)
{
  InfCommunicationHostedGroup* group;
  InfCommunicationHostedGroupPrivate* priv;
  guint i;

  group = INF_COMMUNICATION_HOSTED_GROUP(object);
  priv = INF_COMMUNICATION_HOSTED_GROUP_PRIVATE(group);

  for(i = 0; i < priv->methods->len; ++ i)
    g_free(g_ptr_array_index(priv->methods, i));
  g_ptr_array_free(priv->methods, TRUE);

  G_OBJECT_CLASS(parent_class)->finalize(object);
}
