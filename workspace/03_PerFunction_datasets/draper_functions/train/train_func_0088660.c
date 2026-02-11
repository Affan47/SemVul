client_get_mwm_hints(ObClient *self)
{
    guint num;
    guint32 *hints;

    self->mwmhints.flags = 0;

    if (OBT_PROP_GETA32(self->window, MOTIF_WM_HINTS, MOTIF_WM_HINTS,
                        &hints, &num)) {
        if (num >= OB_MWM_ELEMENTS) {
            self->mwmhints.flags = hints[0];
            self->mwmhints.functions = hints[1];
            self->mwmhints.decorations = hints[2];
        }
        g_free(hints);
    }
}
