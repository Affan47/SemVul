apply_changes         (GtkTreeView *treeview, gboolean new)
{
     GtkTreeSelection *selection;
     GtkTreeModel     *model;
     GtkListStore     *liststore;
     GtkTreeIter       iter;
     const gchar      *qthname;
     const gchar      *qthloc;
     const gchar      *qthdesc;
     const gchar      *qthwx;
     gdouble           qthlat;
     gdouble           qthlon;
     guint             qthalt;
     const gchar      *qthqra;


     qthname = gtk_entry_get_text (GTK_ENTRY (name));
     qthloc  = gtk_entry_get_text (GTK_ENTRY (location));
     qthdesc = gtk_entry_get_text (GTK_ENTRY (desc));
     qthwx   = gtk_entry_get_text (GTK_ENTRY (wx));

     qthlat  = gtk_spin_button_get_value (GTK_SPIN_BUTTON (lat));
     if (gtk_combo_box_get_active (GTK_COMBO_BOX (ns)))
          qthlat = -qthlat;

     qthlon  = gtk_spin_button_get_value (GTK_SPIN_BUTTON (lon));
     if (gtk_combo_box_get_active (GTK_COMBO_BOX (ew)))
          qthlon = -qthlon;

     qthalt = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (alt));


     liststore = GTK_LIST_STORE (gtk_tree_view_get_model (treeview));


     if (new == TRUE) {
          gtk_list_store_append (liststore, &iter);
     }

     else {
          selection = gtk_tree_view_get_selection (treeview);

          if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
               liststore = GTK_LIST_STORE (model);
          }
          else {

               sat_log_log (SAT_LOG_LEVEL_BUG,
                               _("%s:%d: Oooops, gpredict encountered an internal error "\
                                 "(no selection in qth list)"),
                               __FILE__, __LINE__);

               return FALSE;
          }
     }


     gtk_list_store_set (liststore, &iter,
                              QTH_LIST_COL_NAME, qthname,
                              QTH_LIST_COL_LOC, qthloc,
                              QTH_LIST_COL_DESC, qthdesc,
                              QTH_LIST_COL_LAT, qthlat,
                              QTH_LIST_COL_LON, qthlon,
                              QTH_LIST_COL_ALT, qthalt,
                              QTH_LIST_COL_WX, qthwx,
                              -1);

     qthqra  = gtk_entry_get_text (GTK_ENTRY (qra));
     gtk_list_store_set (liststore, &iter,
                              QTH_LIST_COL_QRA, qthqra,
                              -1);

     return TRUE;
}
