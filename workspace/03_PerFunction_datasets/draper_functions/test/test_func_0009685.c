egg_recent_view_gtk_set_icon_size (EggRecentViewGtk *view,
				   GtkIconSize icon_size)
{
	if (view->icon_size != icon_size) {
		view->icon_size = icon_size;
		egg_recent_model_changed (view->model);
	} else {
		view->icon_size = icon_size;
	}
}
