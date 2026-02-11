on_iface_toggled (GtkCellRendererToggle *renderer,
		  gchar                 *path_str,
		  gpointer               data)
{
  GtkTreePath *path;
  GtkTreeModel *model = GTK_TREE_MODEL (data);
  GtkTreeIter iter;
  gboolean active, inconsistent;
  OobsIface *iface;

  path = gtk_tree_path_new_from_string (path_str);

  if (gtk_tree_model_get_iter (model, &iter, path))
    {
      gtk_tree_model_get (model, &iter,
			  COL_ACTIVE, &active,
			  COL_INCONSISTENT, &inconsistent,
			  COL_OBJECT, &iface,
			  -1);

      if (!inconsistent)
	{
	  active ^= 1;

	  oobs_iface_set_active (iface, active);
	  oobs_iface_set_auto (iface, active);
	  ifaces_model_modify_interface_at_iter (&iter);

	  gst_tool_commit_async (tool, OOBS_OBJECT (GST_NETWORK_TOOL (tool)->ifaces_config),
				 _("Changing interface configuration"),
				 on_configuration_changed, tool);
	}

      g_object_unref (iface);
    }

  gtk_tree_path_free (path);
}
