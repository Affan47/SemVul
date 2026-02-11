gnome_rr_config_finalize (GObject *gobject)
{
    GnomeRRConfig *self = GNOME_RR_CONFIG (gobject);

    if (self->priv->screen)
	g_object_unref (self->priv->screen);

    if (self->priv->outputs) {
	int i;

        for (i = 0; self->priv->outputs[i] != NULL; i++) {
	    GnomeRROutputInfo *output = self->priv->outputs[i];
	    g_object_unref (output);
	}
	g_free (self->priv->outputs);
    }

    G_OBJECT_CLASS (gnome_rr_config_parent_class)->finalize (gobject);
}
