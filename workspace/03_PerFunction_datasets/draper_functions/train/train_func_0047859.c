on_project_selection_changed (GladeProject *project, GtkWidget *overlay)
{
  VisibilityData data = { gtk_bin_get_child (GTK_BIN (overlay)), NULL };
  GList *l;

  for (l = glade_project_selection_get (project); l; l = g_list_next (l))
    {
      GtkWidget *selection;

      if (GTK_IS_WIDGET (l->data) && (selection = GTK_WIDGET (l->data)) &&
          overlay != selection)
        data.overlay_child = get_overlay_children (selection, overlay);

      if (data.overlay_child)
        break;
    }

  gtk_container_foreach (GTK_CONTAINER (overlay), set_children_visibility, &data);
}
