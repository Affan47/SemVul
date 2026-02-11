add_selected_sat (GtkListStore *store, gint catnum)
{
    gint        i, sats = 0;
    GtkTreeIter iter;
    GtkTreeIter node;
    gint        catnr;
    gboolean    found = FALSE;
    sat_t       sat;


    sats = gtk_tree_model_iter_n_children (GTK_TREE_MODEL (store), NULL);


    for (i = 0; i < sats; i++) {
        if (gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (store), &iter, NULL, i)) {
            gtk_tree_model_get (GTK_TREE_MODEL (store), &iter,
                                GTK_SAT_SELECTOR_COL_CATNUM, &catnr,
                                -1);
            if (catnum == catnr) {
                found = TRUE;
            }
        }
        else {
            sat_log_log (SAT_LOG_LEVEL_ERROR,
                         _("%s:%s: Could not fetch entry %d in satellite list"),
                         __FILE__, __FUNCTION__, i);
        }

    }

    if (found)
        return;


    if (gtk_sat_data_read_sat (catnum, &sat)) {

        sat_log_log (SAT_LOG_LEVEL_ERROR,
                     _("%s:%s: Error reading satellite %d."),
                     __FILE__, __FUNCTION__, catnum);
    }
    else {

        gtk_list_store_append (store, &node);
        gtk_list_store_set (store, &node,
                            GTK_SAT_SELECTOR_COL_NAME, sat.nickname,
                            GTK_SAT_SELECTOR_COL_CATNUM, catnum,
                            GTK_SAT_SELECTOR_COL_EPOCH, sat.jul_epoch,
                            -1);
        g_free (sat.name);
        g_free (sat.nickname);
    }
}
