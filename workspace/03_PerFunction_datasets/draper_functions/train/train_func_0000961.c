geda_settings_get_entries(GtkWidget *dialog, GedaSettings *geda)
{
  geda->include_dir=update_str(geda->include_dir,
			       get_gtk_entry(dialog, "include_directory_entry"));
  geda->gnetlist_command_line=update_str(geda->gnetlist_command_line,
			       get_gtk_entry(dialog, "gnetlist_command_line_entry"));
  geda->attr=update_str(geda->attr, get_gtk_entry(dialog, "geda_labels_entry"));
  geda->gschem_textsize=update_str(geda->gschem_textsize,
				 get_gtk_entry(dialog, "text_size_entry"));
  geda->gschem_gridsize=update_str(geda->gschem_gridsize,
				   get_gtk_entry(dialog, "snap_size_entry"));

  printf("%d",get_gtk_toggle_button(dialog, "includecwd_yes_radiobutton") );
  if (get_gtk_toggle_button(dialog, "includecwd_yes_radiobutton") == TRUE)
    geda->include_cwd=TRUE;
  else
    geda->include_cwd=FALSE;
  if (get_gtk_toggle_button(dialog, "pinlabel_yes_radiobutton") == TRUE)
    geda->pinlabel_attr=TRUE;
  else
    geda->pinlabel_attr=FALSE;
  if (get_gtk_toggle_button(dialog, "netpriority_nodes_radiobutton") == TRUE)
    geda->gnetlist_priority_node=TRUE;
  else
    geda->gnetlist_priority_node=FALSE;
  if (get_gtk_toggle_button(dialog, "hierarchy_yes_radiobutton") == TRUE)
    geda->gnetlist_hierarchy_allow=TRUE;
  else
    geda->gnetlist_hierarchy_allow=FALSE;
}
