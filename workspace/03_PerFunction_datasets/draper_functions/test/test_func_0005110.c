tp_external_group_mixin_add_members_async (TpSvcChannelInterfaceGroup *obj,
                                           const GArray *contacts,
                                           const gchar *message,
                                           DBusGMethodInvocation *context)
{
  EXTERNAL_OR_DIE (group)
  tp_group_mixin_add_members_async ((TpSvcChannelInterfaceGroup *) group,
      contacts, message, context);
}
