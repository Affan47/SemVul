tp_channel_got_group_flags_0_16_cb (TpChannel *self,
                                    guint flags,
                                    const GError *error,
                                    gpointer user_data G_GNUC_UNUSED,
                                    GObject *weak_object G_GNUC_UNUSED)
{
  g_assert (self->priv->group_flags == 0);

  if (error != NULL)
    {


      _tp_channel_abort_introspection (self, "GetGroupFlags() failed", error);
      return;
    }


  if (flags & TP_CHANNEL_GROUP_FLAG_PROPERTIES)
    {
      DEBUG ("Treason uncloaked! The channel claims to support Group "
          "properties, but GetAll didn't work");
      flags &= ~TP_CHANNEL_GROUP_FLAG_PROPERTIES;
    }

  _got_initial_group_flags (self, flags);
  _tp_channel_continue_introspection (self);
}
