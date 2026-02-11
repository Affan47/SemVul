gdm_session_auditor_finalize (GObject *object)
{
        GdmSessionAuditor *auditor;
        GObjectClass *parent_class;

        auditor = GDM_SESSION_AUDITOR (object);

        g_free (auditor->priv->username);
        g_free (auditor->priv->hostname);
        g_free (auditor->priv->display_device);

        parent_class = G_OBJECT_CLASS (gdm_session_auditor_parent_class);

        if (parent_class->finalize != NULL) {
                parent_class->finalize (object);
        }
}
