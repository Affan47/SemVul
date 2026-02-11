project_changed_cb (GladeProject *project,
                    GladeCommand *command,
                    gboolean      execute,
                    GladeWindow  *window)
{
  GladeProject *active_project = get_active_project (window);

  if (project == active_project)
    refresh_undo_redo (window, project);

  project_queue_autosave (window, project);
}
