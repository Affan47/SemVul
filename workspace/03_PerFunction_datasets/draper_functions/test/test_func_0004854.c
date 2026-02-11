egg_property_cell_renderer_spin_edited_cb (GtkCellRendererText  *renderer,
                                           gchar                *path,
                                           gchar                *new_text,
                                           gpointer              user_data)
{
    EggPropertyCellRendererPrivate *priv;
    gchar *prop_name;

    priv = (EggPropertyCellRendererPrivate *) user_data;
    prop_name = get_prop_name_from_tree_model (GTK_TREE_MODEL (priv->list_store), path);

    if (prop_name != NULL) {
        GParamSpec *pspec;
        GValue from = { 0 };
        GValue to = { 0 };

        pspec = get_pspec_from_object (priv->object, prop_name);

        g_value_init (&from, G_TYPE_DOUBLE);
        g_value_init (&to, pspec->value_type);
        g_value_set_double (&from, strtod (new_text, NULL));

        if (g_value_transform (&from, &to))
            g_object_set_property (priv->object, prop_name, &to);
        else
            g_warning ("Could not transform %s to %s\n",
                    g_value_get_string (&from), g_type_name (pspec->value_type));

        g_free (prop_name);
    }
}
