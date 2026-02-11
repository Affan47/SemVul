magnatune_show_album_list(GtkTreeSelection *selection, gpointer user_data)
{
    MpdData *data = NULL;
    GtkTreeIter piter;
    GTimer *timer;
    GtkTreeModel *model  = gtk_tree_view_get_model(GTK_TREE_VIEW(treeviews[0]));
    if(gtk_tree_selection_get_selected(selection, &model, &piter))
    {
        gchar *genre;
        gtk_tree_model_get(model, &piter, MPDDATA_MODEL_COL_SONG_TITLE,&genre,-1);
        data= magnatune_db_get_artist_list(genre);

        g_free(genre);
    }
    timer = g_timer_new();
    gmpc_mpddata_model_set_mpd_data(GMPC_MPDDATA_MODEL(gtk_tree_view_get_model(GTK_TREE_VIEW(treeviews[1]))),data);
    g_debug("%f seconds elapsed filling artist tree", g_timer_elapsed(timer,NULL)); g_timer_destroy(timer);
}
