list_group_add_members (TpSvcChannelInterfaceGroup *iface,
    const GArray *contacts,
    const gchar *message,
    DBusGMethodInvocation *context)
{
  TpBaseContactListChannel *self = TP_BASE_CONTACT_LIST_CHANNEL (iface);

  if (tp_base_contact_list_channel_check_still_usable (self, context))
    _tp_base_contact_list_add_to_list (self->manager,
        tp_base_channel_get_target_handle ((TpBaseChannel *) self),
        contacts, message, context);
}
