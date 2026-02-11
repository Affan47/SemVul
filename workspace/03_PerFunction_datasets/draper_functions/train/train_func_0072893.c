item_event_file_selector (GooCanvasItem  *item,
			  GooCanvasItem  *target,
			  GdkEventButton *event,
			  gchar *data)
{
  if(!rootitem)
    return FALSE;

  switch (event->type)
    {
    case GDK_BUTTON_PRESS:
      if(!strcmp(data, "/ok/"))	{


	if(strcmp(gtk_entry_get_text(GTK_ENTRY(widget_entry)), "")==0)
	  return FALSE;

	if(fileSelectorCallBack!=NULL)
	  {
	    gchar *result = NULL;
	    gchar *file_type = NULL;

	    if(mode==MODE_SAVE)
	      {
		GtkTreeModel *model;
		GtkTreeIter iter;

		model = gtk_combo_box_get_model ((GtkComboBox *)gtk_combo_filetypes);
		if (gtk_combo_box_get_active_iter ((GtkComboBox *)gtk_combo_filetypes,
						   &iter))
		  gtk_tree_model_get (model, &iter, 0,
				      &file_type, -1);
	      }
	    else
	      file_type = g_strdup(current_extension);

	    result = g_strdup_printf("%s/%s%s",
				     current_rootdir,
				     gtk_entry_get_text(GTK_ENTRY(widget_entry)),
				     (file_type ? file_type :  "") );

	    fileSelectorCallBack(result, file_type, current_user_context);

	    if(file_type)
	      g_free(file_type);


	    if(result)
	      g_free(result);
	  }
	gc_selector_file_stop();
      }
      else if(!strcmp(data, "/cancel/"))
	{
	  gc_selector_file_stop();
	}
      else
	{
	  gchar *ext = g_strrstr(data, ".");
	  gchar *file_wo_ext = g_strdup(data);

	  if(ext)
	    {
	      gchar *ext2 = g_strrstr(file_wo_ext, ".");
	      *ext2 = '\0';
	    }

	  gtk_entry_set_text(GTK_ENTRY(widget_entry),
			     g_path_get_basename(file_wo_ext));
	  g_free(file_wo_ext);


	  if (current_extension && ext)
	    {
	      g_free(current_extension);
	      current_extension = g_strdup(ext);
	    }
	  else if ( ext )
	    current_extension = g_strdup(ext);

	}
      break;
    default:
      break;
    }
  return FALSE;

}
