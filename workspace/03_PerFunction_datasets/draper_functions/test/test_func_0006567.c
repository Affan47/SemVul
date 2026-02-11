toggle_zoom(int flags) {
    if (g_last_seen_mode_rtg) {
        fs_emu_notification(1511162016, _("Zoom is disabled in RTG mode"));
        return;
    }

    if (flags == 1) {
        g_zoom_border = !g_zoom_border;
    }
    else {

        if (g_zoom_modes[g_zoom_mode + 1].name) {
            g_zoom_mode += 1;
        }
        else {
            g_zoom_mode = 0;
        }
    }
    if (g_zoom_border) {
        fs_emu_notification(1511162016, _("Zoom: %s + Border"),
                _(g_zoom_modes[g_zoom_mode].name));
    }
    else {
        fs_emu_notification(1511162016, _("Zoom: %s"),
                _(g_zoom_modes[g_zoom_mode].name));
    }
}
