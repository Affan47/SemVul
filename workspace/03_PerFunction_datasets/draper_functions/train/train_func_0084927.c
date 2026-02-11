_end (void *data, const char *el)
{
  ParserData *pd = data;

  g_free (pd->elem_lang);
  pd->elem_lang = NULL;
  g_free (pd->elem_domain);
  pd->elem_domain = NULL;

  switch (pd->state)
    {
    case STATE_IN_ACTION:
      {
        gchar *vendor;
        gchar *vendor_url;
        gchar *icon_name;
        ParsedAction *action;
        PolkitBackendActionPoolPrivate *priv;

        priv = POLKIT_BACKEND_ACTION_POOL_GET_PRIVATE (pd->pool);

        vendor = pd->vendor;
        if (vendor == NULL)
          vendor = pd->global_vendor;

        vendor_url = pd->vendor_url;
        if (vendor_url == NULL)
          vendor_url = pd->global_vendor_url;

        icon_name = pd->icon_name;
        if (icon_name == NULL)
          icon_name = pd->global_icon_name;

        action = g_new0 (ParsedAction, 1);
        action->action_id = g_strdup (pd->action_id);
        action->vendor_name = g_strdup (vendor);
        action->vendor_url = g_strdup (vendor_url);
        action->icon_name = g_strdup (icon_name);
        action->description = g_strdup (pd->policy_description_nolang);
        action->description_domain = g_strdup (pd->policy_description_domain);
        action->message = g_strdup (pd->policy_message_nolang);
        action->message_domain = g_strdup (pd->policy_message_domain);

        action->localized_description = pd->policy_descriptions;
        action->localized_message     = pd->policy_messages;
        action->annotations           = pd->annotations;

        action->implicit_authorization_any = pd->implicit_authorization_any;
        action->implicit_authorization_inactive = pd->implicit_authorization_inactive;
        action->implicit_authorization_active = pd->implicit_authorization_active;

        g_hash_table_insert (priv->parsed_actions, action->action_id, action);


        pd->annotations = NULL;
        pd->policy_descriptions = NULL;
        pd->policy_messages = NULL;

        break;
      }

    default:
      break;
    }

  --pd->stack_depth;
  if (pd->stack_depth < 0 || pd->stack_depth >= PARSER_MAX_DEPTH)
    {
      g_warning ("reached max depth?");
      goto error;
    }

  if (pd->stack_depth > 0)
    pd->state = pd->state_stack[pd->stack_depth - 1];
  else
    pd->state = STATE_NONE;

  return;

error:
  XML_StopParser (pd->parser, FALSE);
}
