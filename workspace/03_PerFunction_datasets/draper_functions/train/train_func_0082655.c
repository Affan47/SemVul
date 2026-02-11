ide_gen_disk_gui_create(
	unsigned int page,
	const char *name,
	const char *image,
	const char *cylinders,
	const char *heads,
	const char *sectors,
	const char *unit,
	const char *size,
	struct sig_manage *port_manage,
	struct sig_power_device *port_power,
	struct sig_ide_bus *port_ide
)
{
	switch (selected_gui) {
#ifdef HAVE_GTK
	case GUI_GTK:
		return ide_gen_disk_gui_gtk_create(page, name,
				image,
				cylinders, heads, sectors, unit, size,
				port_manage, port_power, port_ide);
		break;
#endif
	case GUI_NULL:
		return (void *) 1;
	default:
		assert(0);
	}

}
