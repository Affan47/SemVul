get_color_array (glColorHistoryModel *this,
                 guint               *n_elements)
{
        GVariant *value;
        GVariant *child_value;
        gsize     i;
        guint    *array;

        value = g_settings_get_value (this->priv->history, "recent-colors");
        *n_elements = g_variant_n_children (value);

        array = g_new0 (guint, *n_elements);

        for ( i = 0; i < *n_elements; i++ )
        {
                child_value = g_variant_get_child_value (value, i);
                array[i] = g_variant_get_uint32 (child_value);
                g_variant_unref (child_value);
        }

        g_variant_unref (value);

        return array;
}
