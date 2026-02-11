mg_create_color_menu(GtkWidget *menu, window_t *sess) {
	GtkWidget *submenu;
	GtkWidget *subsubmenu;
	char buf[256];
	int i;

	submenu = mg_submenu(menu, _("Insert Attribute or Color Code"));

	mg_markup_item(submenu, _("<b>Bold</b>"), 100);
	mg_markup_item(submenu, _("<u>Underline</u>"), 101);

	mg_markup_item(submenu, _("Normal"), 103);

	subsubmenu = mg_submenu(submenu, _("Colors 0-7"));

	for (i = 0; i < 8; i++) {
		sprintf(buf, "<tt><sup>%02d</sup> <span background=\"#%02x%02x%02x\">"
			"   </span></tt>",
			i, colors[i].red >> 8, colors[i].green >> 8, colors[i].blue >> 8);
		mg_markup_item(subsubmenu, buf, i);
	}

	subsubmenu = mg_submenu(submenu, _("Colors 8-15"));

	for (i = 8; i < 16; i++) {
		sprintf(buf, "<tt><sup>%02d</sup> <span background=\"#%02x%02x%02x\">"
			"   </span></tt>",
			i, colors[i].red >> 8, colors[i].green >> 8, colors[i].blue >> 8);
		mg_markup_item(subsubmenu, buf, i);
	}
}
