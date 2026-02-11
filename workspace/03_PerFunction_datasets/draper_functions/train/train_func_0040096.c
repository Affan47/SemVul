gui_gtk_keyboard_deselect(GuiGtkKeyboard *keyboard)
{
	if (! keyboard->active) {
		keyboard->active = 1;

		gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(keyboard->select), 0);

		keyboard->active = 0;
	}
}
