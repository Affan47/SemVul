toplevel_shown (GtkWindow       *toplevel,
                GParamSpec      *pspec,
                NMAMobileWizard *wizard)
{
        gboolean visible = FALSE;

        g_object_get (G_OBJECT (toplevel), "visible", &visible, NULL);
        if (visible)
                nma_mobile_wizard_present (wizard);
}
