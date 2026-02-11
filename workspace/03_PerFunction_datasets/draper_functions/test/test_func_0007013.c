floppy_gen_floppydrive_gui_create(
	unsigned int page,
	const char *name,
	const char *model,
	const char *unit,
	struct sig_manage *port_manage,
	struct sig_power_device *port_power,
	struct sig_shugart_bus *port_shugart,
	struct sig_boolean *port_opt_busy_led,
	struct sig_floppy *port_media,
	struct sig_string *port_change
)
{
	switch (selected_gui) {
#ifdef HAVE_GTK
	case GUI_GTK:
		return floppy_gen_floppydrive_gui_gtk_create(
				page,
				name,
				model,
				unit,
				port_manage,
				port_power,
				port_shugart,
				port_opt_busy_led,
				port_media,
				port_change);
		break;
#endif
	case GUI_NULL:
		return (void *) 1;
	default:
		assert(0);
	}
}
