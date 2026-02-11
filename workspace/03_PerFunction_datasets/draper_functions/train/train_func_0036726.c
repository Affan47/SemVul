store_contains_track(GtkTreeIter * store_iter,
		     GtkTreeIter * __track_iter, char * filename) {


	int i, j, k;
	GtkTreeIter artist_iter;
	GtkTreeIter record_iter;
	GtkTreeIter track_iter;


	i = 0;
	while (gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(music_store),
					     &artist_iter, store_iter, i++)) {
		j = 0;
		while (gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(music_store),
						     &record_iter, &artist_iter, j++)) {
			k = 0;
			while (gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(music_store),
							     &track_iter, &record_iter, k++)) {

				track_data_t * data;

				gtk_tree_model_get(GTK_TREE_MODEL(music_store), &track_iter,
						   MS_COL_DATA, &data, -1);

				if (!strcmp(data->file, filename)) {

					if (__track_iter) {
						*__track_iter = track_iter;
					}

					return 1;
				}
			}
		}
	}

	return 0;
}
