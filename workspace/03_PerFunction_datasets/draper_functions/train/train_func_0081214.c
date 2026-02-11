gsppa_set_roi (GnomeScanPreviewPlugin *gspp)
{
    GSPoint *p;
    GtkPaperSize *ps;
    GtkPageOrientation o;
    gint tmp;

    GnomeScanPreviewPluginArea *gsppa = GNOME_SCAN_PREVIEW_PLUGIN_AREA (gspp);
    gdouble res = gnome_scan_preview_area_get_resolution (GNOME_SCAN_PREVIEW_AREA (gspp->preview_area));
#define	m	gsppa->window
#define	r	gsppa->selection

    p = gnome_scan_settings_get_pointer (gspp->settings, "origin");
    o = gnome_scan_settings_get_enum(gspp->settings, "page-orientation",
                                     GTK_TYPE_PAGE_ORIENTATION);
    if (!p) {
        p = g_new0 (GSPoint, 1);
        gnome_scan_settings_set_pointer (gspp->settings, "origin", p);
    }

    r.x = gs_convert_from_mm (p->x, GS_UNIT_PIXEL, res);
    r.y = gs_convert_from_mm (p->y, GS_UNIT_PIXEL, res);

    ps = gnome_scan_settings_get_boxed (gspp->settings, "paper-size",
                                        GTK_TYPE_PAPER_SIZE);

    r.width = (gint) gs_convert_from_mm (gtk_paper_size_get_width (ps, GTK_UNIT_MM), GS_UNIT_PIXEL, res);
    r.height = (gint) gs_convert_from_mm (gtk_paper_size_get_height (ps, GTK_UNIT_MM), GS_UNIT_PIXEL, res);

    switch(o) {
        case GTK_PAGE_ORIENTATION_LANDSCAPE:
        case GTK_PAGE_ORIENTATION_REVERSE_LANDSCAPE:
            tmp = r.width;
            r.width = MAX(r.width, r.height);
            r.height = MIN(tmp, r.height);
            break;
        case GTK_PAGE_ORIENTATION_PORTRAIT:
        case GTK_PAGE_ORIENTATION_REVERSE_PORTRAIT:
            tmp = r.width;
            r.width = MIN(r.width, r.height);
            r.height = MAX(tmp, r.height);
            break;
    }

    gsppa->cf = gsppa_get_cursor_flag_for_paper_size (ps);

    gnome_scan_preview_area_get_size (GNOME_SCAN_PREVIEW_AREA (gspp->preview_area),
                                      &m.width,
                                      &m.height);

#undef	m
#undef	r
}
