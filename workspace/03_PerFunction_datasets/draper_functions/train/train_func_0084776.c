lekhonee_main_populate_posts (LekhoneeMain* self, GValueArray* values) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (values != NULL);
	{
		gint i;
		i = 0;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				GHashTable* hash;
				GValue* val;
				GtkTreeIter _tmp1_ = {0};
				GtkTreeIter iter;
				if (!_tmp0_) {
					i++;
				}
				_tmp0_ = FALSE;
				if (!(i < values->n_values)) {
					break;
				}
				hash = _g_hash_table_ref0 (g_value_get_boxed (g_value_array_get_nth (values, (guint) i)));
				val = __g_value_dup0 ((GValue*) g_hash_table_lookup (hash, "title"));
				iter = (_tmp1_);
				gtk_list_store_append (self->liststore2, &iter);
				gtk_list_store_set (self->liststore2, &iter, 0, g_value_get_string (val), -1);
				gtk_list_store_set (self->liststore2, &iter, 1, hash, -1);
				_g_hash_table_unref0 (hash);
				_g_free0 (val);
			}
		}
	}
	g_source_remove (self->vid);
	gtk_progress_bar_set_fraction (self->progressbar, 0.0);
	gtk_progress_bar_set_text (self->progressbar, "");
	gtk_widget_hide_all ((GtkWidget*) self->progressbar);
}
