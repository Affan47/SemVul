handle_widget_event(SDL_Event *event)
{
	struct widget *ui = get_active_ui();

	if (ui)
		ui->handle_event(ui, event);
}
