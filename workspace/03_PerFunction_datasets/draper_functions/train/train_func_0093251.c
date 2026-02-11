ibus_property_destroy (IBusProperty *prop)
{
    g_free (prop->priv->key);
    prop->priv->key = NULL;

    g_free (prop->priv->icon);
    prop->priv->icon = NULL;

    if (prop->priv->label) {
        g_object_unref (prop->priv->label);
        prop->priv->label = NULL;
    }

    if (prop->priv->symbol) {
        g_object_unref (prop->priv->symbol);
        prop->priv->symbol = NULL;
    }

    if (prop->priv->tooltip) {
        g_object_unref (prop->priv->tooltip);
        prop->priv->tooltip = NULL;
    }

    if (prop->priv->sub_props) {
        g_object_unref (prop->priv->sub_props);
        prop->priv->sub_props = NULL;
    }

    IBUS_OBJECT_CLASS (ibus_property_parent_class)->destroy ((IBusObject *)prop);
}
