entangle_dpms_set_blanking(gboolean enabled,
                                    GError **error)
{
    GdkDisplay *dpy = gdk_display_get_default();

    ENTANGLE_DEBUG("Toggle set blanking %d", enabled);

#if defined(HAVE_XEXT) && defined(GDK_WINDOWING_X11)
    if (GDK_IS_X11_DISPLAY(dpy)) {
        Display *xdpy = gdk_x11_display_get_xdisplay(dpy);
        int ignore1, ignore2;

        if (!DPMSQueryExtension(xdpy, &ignore1, &ignore2) ||
            !DPMSCapable(xdpy)) {
            ENTANGLE_ERROR(error, "%s",
                           _("Screen blanking is not available on this display"));
            return FALSE;
        }

        DPMSEnable(xdpy);
        DPMSForceLevel(xdpy, enabled ? DPMSModeStandby : DPMSModeOn);

        return TRUE;
    }
#endif

    ENTANGLE_ERROR(error, "%s",
                   _("Screen blanking is not implemented on this platform"));
    return FALSE;
}
