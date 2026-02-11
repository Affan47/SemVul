tp_presence_mixin_emit_presence_update (GObject *obj,
                                        GHashTable *contact_statuses)
{
  TpPresenceMixinClass *mixin_cls =
    TP_PRESENCE_MIXIN_CLASS (G_OBJECT_GET_CLASS (obj));
  GHashTable *presence_hash;

  DEBUG ("called.");

  if (g_type_interface_peek (G_OBJECT_GET_CLASS (obj),
      TP_TYPE_SVC_CONNECTION_INTERFACE_PRESENCE) != NULL)
    {
      presence_hash = construct_presence_hash (mixin_cls->statuses,
          contact_statuses);
      tp_svc_connection_interface_presence_emit_presence_update (obj,
          presence_hash);

      g_hash_table_unref (presence_hash);
    }

  if (g_type_interface_peek (G_OBJECT_GET_CLASS (obj),
      TP_TYPE_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE) != NULL)
    {
      presence_hash = construct_simple_presence_hash (mixin_cls->statuses,
        contact_statuses);
      tp_svc_connection_interface_simple_presence_emit_presences_changed (obj,
        presence_hash);

      g_hash_table_unref (presence_hash);
    }
}
