set_cursor (GdkCursor *gdk_cursor)
{
	GladeProject *project;
	GList        *list, *projects;

	for (projects = glade_app_get_projects ();
	     projects; projects = projects->next)
	{
		project = projects->data;

		for (list = (GList *) glade_project_get_objects (project);
		     list; list = list->next)
		{
			GObject *object = list->data;

			if (GTK_IS_WINDOW (object))
			{
				set_cursor_recurse (GTK_WIDGET (object), gdk_cursor);
			}
		}
	}
}
