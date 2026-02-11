gog_chart_view_render (GogView *view, GogViewAllocation const *bbox)
{
	GSList *ptr;
	GogView *child_view;
	gboolean grid_line_rendered = FALSE;
	GogChart *chart = GOG_CHART (gog_view_get_model (view));

	cview_parent_klass->render (view, bbox);

	if (gog_chart_is_3d (chart)) {
		for (ptr = view->children ; ptr != NULL ; ptr = ptr->next) {
			child_view = ptr->data;
			if (!GOG_IS_AXIS (child_view->model) && !GOG_IS_PLOT (child_view->model) && !GOG_IS_LABEL (child_view->model))
				gog_view_render	(ptr->data, bbox);
		}

		for (ptr = view->children ; ptr != NULL ; ptr = ptr->next) {
			child_view = ptr->data;
			if (!GOG_IS_AXIS (child_view->model))
				continue;
			gog_view_render (ptr->data, bbox);
			grid_line_render (ptr, bbox);
		}
		for (ptr = view->children ; ptr != NULL ; ptr = ptr->next) {
			child_view = ptr->data;
			if (!GOG_IS_PLOT (child_view->model))
				continue;
			gog_view_render	(ptr->data, bbox);
		}
	} else {

		for (ptr = view->children ; ptr != NULL ; ptr = ptr->next) {
			child_view = ptr->data;
			if (!grid_line_rendered && GOG_IS_AXIS (child_view->model)) {
				plot_render (view, bbox, GOG_PLOT_RENDERING_BEFORE_GRID);
				grid_line_render (ptr, bbox);
				plot_render (view, bbox, GOG_PLOT_RENDERING_BEFORE_AXIS);
				grid_line_rendered = TRUE;
			}
			if (GOG_IS_PLOT (child_view->model)) {
			    if (!GOG_PLOT (child_view->model)->rendering_order)
				gog_view_render	(ptr->data, bbox);
			} else if (!GOG_IS_LABEL (child_view->model))
				gog_view_render	(ptr->data, bbox);
		}
	}
	for (ptr = view->children ; ptr != NULL ; ptr = ptr->next) {
		child_view = ptr->data;
		if (!GOG_IS_LABEL (child_view->model))
			continue;
		gog_view_render	(ptr->data, bbox);
	}
}
