connect_view (GalViewInstance *instance,
              GalView *view)
{
	GalViewClass *view_class;

	if (instance->current_view)
		disconnect_view (instance);
	instance->current_view = g_object_ref (view);

	view_class = GAL_VIEW_GET_CLASS (view);

	instance->current_title = g_strdup (gal_view_get_title (view));
	instance->current_type = g_strdup (view_class->type_code);
	instance->view_changed_id = g_signal_connect (
		instance->current_view, "changed",
		G_CALLBACK (view_changed), instance);

	gal_view_instance_display_view (instance, instance->current_view);
}
