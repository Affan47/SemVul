eog_list_store_add_thumbnail_job (EogListStore *store, GtkTreeIter *iter)
{
	EogImage *image;
	EogJob *job;

	gtk_tree_model_get (GTK_TREE_MODEL (store), iter,
			    EOG_LIST_STORE_EOG_IMAGE, &image,
			    EOG_LIST_STORE_EOG_JOB, &job,
			    -1);

	if (job != NULL) {
		g_object_unref (image);
		return;
	}

	job = eog_job_thumbnail_new (image);

	g_signal_connect (job,
			  "finished",
			  G_CALLBACK (eog_job_thumbnail_cb),
			  store);

	g_mutex_lock (&store->priv->mutex);
	gtk_list_store_set (GTK_LIST_STORE (store), iter,
			    EOG_LIST_STORE_EOG_JOB, job,
			    -1);
	eog_job_scheduler_add_job (job);
	g_mutex_unlock (&store->priv->mutex);
	g_object_unref (job);
	g_object_unref (image);
}
