dispose (GObject *object)
{
        DhAssistant *assistant = DH_ASSISTANT (object);
        DhAssistantPriv *priv = GET_PRIVATE (assistant);
        g_clear_object (&priv->application);
        g_clear_object (&priv->settings);

        G_OBJECT_CLASS (dh_assistant_parent_class)->dispose (object);
}
