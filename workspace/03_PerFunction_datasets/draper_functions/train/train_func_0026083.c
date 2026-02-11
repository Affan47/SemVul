CallBack_toggle_float_message(GtkWidget* widget) {
	(void)widget;

	if(global->phase != PHASE_GAMEPLAY) return;

	game->message_float = !game->message_float;
	interface_message_and_chat_float_unfloat();
}
