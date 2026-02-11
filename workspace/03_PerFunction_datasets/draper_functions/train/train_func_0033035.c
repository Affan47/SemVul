rafresh_perspective_button()
{
	GtkAction * action = gtk_ui_manager_get_action(manager, "/ToolbarGL/RenderPerspective");

	if(GTK_IS_TOGGLE_ACTION(action))
	{
  		gboolean perspective = FALSE;
  		gdouble aspect, zn, zf, zo;
		get_camera_values(&zn, &zf, &zo, &aspect, &perspective);
		gtk_toggle_action_set_active(GTK_TOGGLE_ACTION(action), perspective);

	}
}
