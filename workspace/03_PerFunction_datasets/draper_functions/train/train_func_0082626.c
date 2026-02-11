onPlayStopClicked(GtkToggleButton *button, gpointer data _U_)
{
  GtkTreeIter startIter;
  gboolean res, checked, hasChild;
  gulong *playCallbackId;

  DBG_fprintf(stderr, "Panel Browser: toggle on play button.\n");


  if (gtk_toggle_button_get_active(button))
    {

      checked = FALSE;
      res = visu_ui_panel_browser_getCurrentSelected(&startBrowsePath, &startIter);
      if (res)
        {
          gtk_tree_model_get(GTK_TREE_MODEL(treeFilesSortable), &startIter,
                             COLUMN_BOOLEAN, &checked, -1);
          hasChild = gtk_tree_model_iter_has_child(GTK_TREE_MODEL(treeFilesSortable),
                                                   &startIter);
        }
      if (!res || !checked || hasChild)
	{
	  res = visu_ui_panel_browser_getNextSelected(&startBrowsePath, &startIter,
					     VISU_UI_PANEL_BROWSER_NEXT);
	  if (!res)
	    {
	      startBrowsePath = gtk_tree_path_new();

	      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(buttonPlayStop), FALSE);
	      return;
	    }
	}
      navigateInFiles(startBrowsePath, &startIter);


      gtk_widget_hide(imagePlay);
      gtk_widget_show(imageStop);

      currentBrowseDirection = VISU_UI_PANEL_BROWSER_NEXT;
      playCallbackId = g_malloc(sizeof(gulong));
      *playCallbackId =
	g_timeout_add_full(G_PRIORITY_HIGH_IDLE,
			   (gint)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spinDelay)),
			   playSelectedFiles, (gpointer)0,
			   stopPlayStop);
      g_object_set_data(G_OBJECT(button), "playCallbackId",
			(gpointer)playCallbackId);
      DBG_fprintf(stderr, " | start play\n");
    }
  else
    {

      playCallbackId = (gulong*)g_object_get_data(G_OBJECT(button), "playCallbackId");
      if (playCallbackId)
	g_source_remove(*playCallbackId);
      DBG_fprintf(stderr, " | stop play\n");
    }
}
