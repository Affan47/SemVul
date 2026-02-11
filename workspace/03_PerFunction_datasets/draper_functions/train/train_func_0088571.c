tp_base_contact_list_dup_states (TpBaseContactList *self,
    TpHandle contact,
    TpSubscriptionState *subscribe,
    TpSubscriptionState *publish,
    gchar **publish_request)
{
  TpBaseContactListClass *cls = TP_BASE_CONTACT_LIST_GET_CLASS (self);

  g_return_if_fail (cls != NULL);
  g_return_if_fail (cls->dup_states != NULL);
  g_return_if_fail (tp_base_contact_list_get_state (self, NULL) ==
      TP_CONTACT_LIST_STATE_SUCCESS);

  cls->dup_states (self, contact, subscribe, publish, publish_request);

  if (publish_request != NULL && *publish_request == NULL)
    *publish_request = g_strdup ("");
}
