inf_communication_manager_open_group(InfCommunicationManager* manager,
                                     const gchar* group_name,
                                     const gchar* const* methods)
{
  InfCommunicationManagerPrivate* priv;
  InfCommunicationHostedGroup* group;
  const gchar* const* method;

  g_return_val_if_fail(INF_COMMUNICATION_IS_MANAGER(manager), NULL);
  g_return_val_if_fail(group_name != NULL, NULL);

  priv = INF_COMMUNICATION_MANAGER_PRIVATE(manager);

  g_return_val_if_fail(
    g_hash_table_lookup(priv->hosted_groups, group_name) == NULL,
    NULL
  );

  group = g_object_new(
    INF_COMMUNICATION_TYPE_HOSTED_GROUP,
    "communication-manager", manager,
    "communication-registry", priv->registry,
    "name", group_name,
    NULL
  );

  if(methods != NULL)
  {
    for(method = methods; *method != NULL; ++ method)
      inf_communication_hosted_group_add_method(group, *method);
  }

  g_hash_table_insert(
    priv->hosted_groups,
    *(gpointer*) (gpointer) &group_name,
    group
  );

  g_object_weak_ref(
    G_OBJECT(group),
    inf_communication_manager_hosted_group_unrefed,
    manager
  );

  return group;
}
