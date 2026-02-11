ibus_component_copy (IBusComponent       *dest,
                     const IBusComponent *src)
{
    gboolean retval;

    retval = IBUS_SERIALIZABLE_CLASS (ibus_component_parent_class)->copy ((IBusSerializable *)dest,
                                 (IBusSerializable *)src);
    g_return_val_if_fail (retval, FALSE);

    dest->priv->name          = g_strdup (src->priv->name);
    dest->priv->description   = g_strdup (src->priv->description);
    dest->priv->version       = g_strdup (src->priv->version);
    dest->priv->license       = g_strdup (src->priv->license);
    dest->priv->author        = g_strdup (src->priv->author);
    dest->priv->homepage      = g_strdup (src->priv->homepage);
    dest->priv->exec          = g_strdup (src->priv->exec);
    dest->priv->textdomain    = g_strdup (src->priv->textdomain);

    dest->priv->observed_paths = g_list_copy (src->priv->observed_paths);
    g_list_foreach (dest->priv->observed_paths, (GFunc) g_object_ref, NULL);

    dest->priv->engines = g_list_copy (src->priv->engines);
    g_list_foreach (dest->priv->engines, (GFunc) g_object_ref, NULL);

    return TRUE;
}
