monitor_gui_create(
	unsigned int page,
	const char *name,
	struct sig_manage *port_manage,
	struct sig_boolean *port_power_230v,
	struct sig_vga *port_vga,
	struct sig_opt_rgb *port_opt_video,
	struct sig_boolean *port_screenshot,
	struct sig_boolean *port_rec
)
{
	switch (selected_gui) {
#ifdef HAVE_GTK
	case GUI_GTK:
		return monitor_gui_gtk_create(page, name,
				port_manage,
				port_power_230v,
				port_vga,
				port_opt_video,
				port_screenshot,
				port_rec);
		break;
#endif
	case GUI_NULL:
		return monitor_gui_null_create(page, name,
				port_manage,
				port_power_230v,
				port_vga,
				port_opt_video,
				port_screenshot,
				port_rec);
		break;
	default:
		assert(0);
	}
}
