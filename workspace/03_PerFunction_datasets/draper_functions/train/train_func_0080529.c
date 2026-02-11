get_messages (TpSvcDebug *self,
    DBusGMethodInvocation *context)
{
  TpDebugSender *dbg = TP_DEBUG_SENDER (self);
  GPtrArray *messages;
  GList *i;
  guint j;

  messages = g_ptr_array_sized_new (g_queue_get_length (dbg->priv->messages));

  for (i = dbg->priv->messages->head; i; i = i->next)
    {
      GValue gvalue = { 0 };
      DebugMessage *message = (DebugMessage *) i->data;

      g_value_init (&gvalue, TP_STRUCT_TYPE_DEBUG_MESSAGE);
      g_value_take_boxed (&gvalue,
          dbus_g_type_specialized_construct (TP_STRUCT_TYPE_DEBUG_MESSAGE));
      dbus_g_type_struct_set (&gvalue,
          0, message->timestamp,
          1, message->domain,
          2, message->level,
          3, message->string,
          G_MAXUINT);
      g_ptr_array_add (messages, g_value_get_boxed (&gvalue));
    }

  tp_svc_debug_return_from_get_messages (context, messages);

  for (j = 0; j < messages->len; j++)
    g_boxed_free (TP_STRUCT_TYPE_DEBUG_MESSAGE, messages->pdata[j]);

  g_ptr_array_unref (messages);
}
