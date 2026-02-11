gnome_bg_draw (GnomeBG *bg,
	       GdkPixbuf *dest,
	       GdkScreen *screen,
	       gboolean is_root)
{
	if (!bg)
		return;

	if (is_root && (bg->placement != G_DESKTOP_BACKGROUND_STYLE_SPANNED)) {
		draw_color_each_monitor (bg, dest, screen);
		if (bg->placement != G_DESKTOP_BACKGROUND_STYLE_NONE) {
			draw_each_monitor (bg, dest, screen);
		}
	} else {
		draw_color (bg, dest);
		if (bg->placement != G_DESKTOP_BACKGROUND_STYLE_NONE) {
			draw_once (bg, dest);
		}
	}
}
