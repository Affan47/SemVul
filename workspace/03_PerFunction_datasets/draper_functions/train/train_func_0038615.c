chat_area_set_property (GObject* obj,
			guint prop_id,
			const GValue* value,
			GParamSpec* spec)
{
  ChatArea* self = NULL;
  gpointer ptr = NULL;

  self = (ChatArea* )obj;

  switch (prop_id) {

  case CHAT_AREA_PROP_CHAT:
    ptr = g_value_get_pointer (value);
    self->priv->chat = (Ekiga::Chat *)ptr;
    self->priv->connection = self->priv->chat->removed.connect (boost::bind (&on_chat_removed, self));
    self->priv->helper = boost::shared_ptr<ChatAreaHelper>(new ChatAreaHelper (self));
    self->priv->chat->connect (self->priv->helper);
    break;

  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, prop_id, spec);
    break;
  }
}
