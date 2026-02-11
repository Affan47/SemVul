jamendo_show_song_list(GtkTreeSelection *selection, gpointer user_data)
{
    MpdData *data = NULL;
    GtkTreeIter piter;
    GtkTreeSelection *select = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeviews[0]));
    GtkTreeModel *model  = gtk_tree_view_get_model(GTK_TREE_VIEW(treeviews[0]));
    gchar *genre = NULL, *artist = NULL, *album = NULL;
    if(gtk_tree_selection_get_selected(select, &model, &piter))
    {

        select = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeviews[1]));
        gtk_tree_model_get(model, &piter, MPDDATA_MODEL_COL_SONG_TITLE,&genre,-1);

        model  = gtk_tree_view_get_model(GTK_TREE_VIEW(treeviews[1]));
        if(gtk_tree_selection_get_selected(select, &model, &piter))
        {
            gtk_tree_model_get(model, &piter, MPDDATA_MODEL_COL_SONG_TITLE,&artist,-1);
            select = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeviews[2]));
            model  = gtk_tree_view_get_model(GTK_TREE_VIEW(treeviews[2]));
            if(gtk_tree_selection_get_selected(select, &model, &piter))
            {
                gtk_tree_model_get(model, &piter, MPDDATA_MODEL_COL_SONG_TITLE,&album,-1);
            }
        }
    }
    data = jamendo_db_get_song_list(genre, artist, album,TRUE);
    gmpc_mpddata_model_set_mpd_data(GMPC_MPDDATA_MODEL(mt_store), data);
}
