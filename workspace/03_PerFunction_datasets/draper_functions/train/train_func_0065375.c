dh_base_new_assistant (DhBase *base)
{
        DhBasePriv *priv;
        GtkWidget  *assistant;

        g_return_val_if_fail (DH_IS_BASE (base), NULL);

        priv = GET_PRIVATE (base);

        assistant = dh_assistant_new (base);

        priv->assistants = g_slist_prepend (priv->assistants, assistant);

        g_object_weak_ref (G_OBJECT (assistant),
                           (GWeakNotify) base_window_or_assistant_finalized_cb,
                           base);

        return assistant;
}
