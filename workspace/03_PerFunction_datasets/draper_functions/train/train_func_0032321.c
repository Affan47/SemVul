set_color_array (glColorHistoryModel *this,
                 guint               *array,
                 guint                n_elements)
{
        GVariant  *value;
        GVariant **child_values;
        gsize      i;

        child_values = g_new (GVariant *, n_elements);

        for ( i = 0; i < n_elements; i++ )
        {
                child_values[i] = g_variant_new_uint32 (array[i]);
        }

        value = g_variant_new_array (G_VARIANT_TYPE_UINT32, child_values, n_elements);

        g_settings_set_value (this->priv->history, "recent-colors", value);

        g_free (child_values);
}
