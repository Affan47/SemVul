elevator_rc_simple_led_set(void *_cpssp, unsigned int val)
{
	struct elevator_rc_simple_led * cpssp = (struct elevator_rc_simple_led *) _cpssp;

	if (val == SIG_STD_LOGIC_1) {
		gtk_image_set_from_icon_name(GTK_IMAGE(cpssp->led), "gtk-yes", GTK_ICON_SIZE_BUTTON);
	} else {
		gtk_image_set_from_icon_name(GTK_IMAGE(cpssp->led), "gtk-no", GTK_ICON_SIZE_BUTTON);
	}
	gui_gtk_flush();
}
