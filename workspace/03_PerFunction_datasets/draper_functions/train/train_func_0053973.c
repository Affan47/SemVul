display_contact (TpContact *contact)
{
  const gchar *avatar_token;

  g_message ("Handle %u, \"%s\":", tp_contact_get_handle (contact),
      tp_contact_get_identifier (contact));
  g_message ("\tAlias: \"%s\"", tp_contact_get_alias (contact));

  avatar_token = tp_contact_get_avatar_token (contact);

  if (avatar_token == NULL)
    g_message ("\tAvatar token not known");
  else
    g_message ("\tAvatar token: \"%s\"", avatar_token);

  g_message ("\tPresence: type #%i \"%s\": \"%s\"",
      tp_contact_get_presence_type (contact),
      tp_contact_get_presence_status (contact),
      tp_contact_get_presence_message (contact));
}
