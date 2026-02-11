activate_action (GtkToolButton *toolbutton,
				      GladeWidgetAction *action)
{
	GladeWidget *widget;

	if ((widget = g_object_get_data (G_OBJECT (toolbutton), "glade-widget")))
		glade_widget_adaptor_action_activate (widget->adaptor,
						      widget->object,
						      action->klass->path);
}
