gog_graph_view_size_allocate (GogView *view, GogViewAllocation const *bbox)
{
	GSList *ptr;
	double h, w;
	GogView *child;
	GogGraph *graph = GOG_GRAPH (view->model);
	GogViewAllocation tmp, res = *bbox;

	(gview_parent_klass->size_allocate) (view, &res);

	if (gog_graph_num_cols (graph) <= 0 ||
	    gog_graph_num_rows (graph) <= 0)
		return;

	res = view->residual;
	w = res.w / gog_graph_num_cols (graph);
	h = res.h / gog_graph_num_rows (graph);
	for (ptr = view->children; ptr != NULL ; ptr = ptr->next) {
		child = ptr->data;
		if (GOG_POSITION_IS_SPECIAL (child->model->position)) {
			GogChart *chart = GOG_CHART (child->model);
			tmp.x = chart->x_pos_actual * w + res.x;
			tmp.y = chart->y_pos_actual * h + res.y;
			tmp.w = chart->cols * w;
			tmp.h = chart->rows * h;
			gog_view_size_allocate (child, &tmp);
		}
	}
}
