cph_mechanism_constructor (GType                  type,
                           guint                  n_construct_properties,
                           GObjectConstructParam *construct_properties)
{
        GObject      *obj;
        CphMechanism *mechanism;

        obj = G_OBJECT_CLASS (cph_mechanism_parent_class)->constructor (
                                                type,
                                                n_construct_properties,
                                                construct_properties);

        mechanism = CPH_MECHANISM (obj);
        mechanism->priv->cups = cph_cups_new ();

        if (!mechanism->priv->cups) {
                g_object_unref (mechanism);
                return NULL;
        }

        return obj;
}
