selectionChanged(GtkTreeSelection *tree _U_, gpointer data)
{
  gboolean select, isChild, hasChild;
  VisuUiPairsIter iter;
  GtkTreeIter iterParent;
  struct specBuildFunc_struct *spec;

  DBG_fprintf(stderr, "Gtk Pairs: selection changed.\n");
  select = FALSE;
  isChild = FALSE;
  hasChild = FALSE;
  for (visu_ui_pairs_iter_startSelected(&iter); iter.data;
       visu_ui_pairs_iter_nextSelected(&iter))
    {
      select = TRUE;

      if (!iter.current)
	{

	  g_signal_handler_block(G_OBJECT(gtkPairs_spinMin),
				 gtkPairs_spinMinSignalId);
	  g_signal_handler_block(G_OBJECT(gtkPairs_spinMax),
				 gtkPairs_spinMaxSignalId);
	  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtkPairs_spinMin),
				    visu_pair_link_getDistance(iter.data, VISU_PAIR_DISTANCE_MIN));
	  gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtkPairs_spinMax),
				    visu_pair_link_getDistance(iter.data, VISU_PAIR_DISTANCE_MAX));
	  g_signal_handler_unblock(G_OBJECT(gtkPairs_spinMax),
				   gtkPairs_spinMaxSignalId);
	  g_signal_handler_unblock(G_OBJECT(gtkPairs_spinMin),
				   gtkPairs_spinMinSignalId);


          g_signal_handler_block(G_OBJECT(widgetColor), widgetColorSignalId);
          visu_ui_color_combobox_setSelection(VISU_UI_COLOR_COMBOBOX(widgetColor),
                                              visu_pair_link_getColor(iter.data));
          g_signal_handler_unblock(G_OBJECT(widgetColor), widgetColorSignalId);


          spec = getSpecBuildFuncs(iter.data);
          if (spec)
            {
              showSpecArea(spec);
              if (spec->selected)
                spec->selected(iter.data);
	      g_signal_handler_block(G_OBJECT(data), methodSignalId);
              selectByPairMethod(GTK_COMBO_BOX(data),
                                 visu_gl_ext_pairs_getDrawMethod(visu_gl_ext_pairs_getDefault(), iter.data));
	      g_signal_handler_unblock(G_OBJECT(data), methodSignalId);
            }

	  isChild = gtk_tree_model_iter_parent(GTK_TREE_MODEL(pairsTreeStore),
						&iterParent, &(iter.iter));
	  hasChild = gtk_tree_model_iter_has_child(GTK_TREE_MODEL(pairsTreeStore),
						   &(iter.iter));
	}
    }


  gtk_widget_set_sensitive(alignWidget, select);
  gtk_widget_set_sensitive(btAdd, select);
  gtk_widget_set_sensitive(btRemove, select && (isChild || hasChild));
}
