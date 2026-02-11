update_widgets (GtkTreeView *treeview)
{
     GtkTreeSelection *selection;
     GtkTreeModel     *model;
     GtkTreeIter       iter;
     gchar            *qthname;
     gchar            *qthdesc;
     gchar            *qthloc;
     gdouble           qthlat;
     gdouble           qthlon;
     guint             qthalt;
     gchar            *qthwx;


     selection = gtk_tree_view_get_selection (treeview);

     if (gtk_tree_selection_get_selected (selection, &model, &iter)) {


          gtk_tree_model_get (model, &iter,
                                   QTH_LIST_COL_NAME, &qthname,
                                   QTH_LIST_COL_LOC,  &qthloc,
                                   QTH_LIST_COL_DESC, &qthdesc,
                                   QTH_LIST_COL_LAT, &qthlat,
                                   QTH_LIST_COL_LON, &qthlon,
                                   QTH_LIST_COL_ALT, &qthalt,
                                   QTH_LIST_COL_WX, &qthwx,
                                   -1);


          if (qthname) {
               gtk_entry_set_text (GTK_ENTRY (name), qthname);
          }

          if (qthloc) {
               gtk_entry_set_text (GTK_ENTRY (location), qthloc);
               g_free (qthloc);
          }

          if (qthdesc) {
               gtk_entry_set_text (GTK_ENTRY (desc), qthdesc);
               g_free (qthdesc);
          }

          if (qthwx) {
               gtk_entry_set_text (GTK_ENTRY (wx), qthwx);
               g_free (qthwx);
          }

          if (qthlat < 0.00)
               gtk_combo_box_set_active (GTK_COMBO_BOX (ns), 1);
          else
               gtk_combo_box_set_active (GTK_COMBO_BOX (ns), 0);

          gtk_spin_button_set_value (GTK_SPIN_BUTTON (lat), fabs (qthlat));

          if (qthlon < 0.00)
               gtk_combo_box_set_active (GTK_COMBO_BOX (ew), 1);
          else
               gtk_combo_box_set_active (GTK_COMBO_BOX (ew), 0);

          gtk_spin_button_set_value (GTK_SPIN_BUTTON (lon), fabs (qthlon));

          gtk_spin_button_set_value (GTK_SPIN_BUTTON (alt), qthalt);

          sat_log_log (SAT_LOG_LEVEL_DEBUG,
                          _("%s:%d: Loaded %s for editing:\n"\
                            "LAT:%.4f LON:%.4f ALT:%d"),
                          __FILE__, __LINE__,
                          (qthname != NULL) ? qthname : "???",
                          qthlat, qthlon, qthalt);

          g_free (qthname);

     }
     else {
          sat_log_log (SAT_LOG_LEVEL_BUG,
                          _("%s:%d: No ground station selected!"),
                          __FILE__, __LINE__);
     }
}
