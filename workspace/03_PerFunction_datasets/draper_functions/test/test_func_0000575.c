gog_tool_move_pie_init (GogToolAction *action)
{
	GogPiePlot *pie = GOG_PIE_PLOT (action->view->model);
	MovePieData *data = g_new0 (MovePieData, 1);
	GogViewAllocation area = action->view->allocation;

	data->r = area.h;
	if (data->r > area.w)
		data->r = area.w;
	data->r /= 2.;
	data->start_pos = (data->r * (0.5 + pie->default_separation)) / (1 + pie->default_separation);
	data->x = area.x + area.w / 2.;
	data->y = area.y + area.h / 2.;
	data->start_distance = hypot (action->start_x - data->x, action->start_y - data->y);

	action->data = data;
}
