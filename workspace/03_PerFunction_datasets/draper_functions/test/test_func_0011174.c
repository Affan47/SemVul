show_multi()
{
	EB_Error_Code error_code;
	BOOK_INFO *binfo;
	gchar label[256];
	gchar *utf_str;
	gint i;

 	EB_Multi_Search_Code multi_codes[EB_MAX_MULTI_SEARCHES];
	int multi_count;
	GtkTreeIter   parent_iter;
	GtkTreeIter   child_iter;
	GtkTreeIter   dict_parent_iter;
	GtkTreeIter   dict_child_iter;
	gboolean has_active;
	gboolean active;

	LOG(LOG_DEBUG, "IN : show_multi()");

	gtk_tree_store_clear(multi_store);

	has_active = FALSE;

	if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(dict_store), &dict_parent_iter) == TRUE){
		do {
			gtk_tree_model_get (GTK_TREE_MODEL(dict_store),
					    &dict_parent_iter,
					    DICT_ACTIVE_COLUMN, &active,
					    -1);

			if(active) {
				has_active = TRUE;
				break;
			}
	       } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(dict_store), &dict_parent_iter) == TRUE);
	}


	if(has_active == FALSE) {
		LOG(LOG_INFO, "no active group");
		return;
	}

	if(gtk_tree_model_iter_children(GTK_TREE_MODEL(dict_store), &dict_child_iter, &dict_parent_iter) == TRUE){
		do {
			gtk_tree_model_get(GTK_TREE_MODEL(dict_store),
					   &dict_child_iter,
					   DICT_ACTIVE_COLUMN, &active,
					   DICT_MEMBER_COLUMN, &binfo,
					   -1);

			if(active == FALSE)
				continue;

			if(binfo->search_method[SEARCH_METHOD_MULTI] != TRUE)
				continue;


			error_code = eb_multi_search_list(binfo->book, multi_codes, &multi_count);
			if(error_code  != EB_SUCCESS) {
				LOG(LOG_CRITICAL, "Failed to list multi search : %s\n",
				    eb_error_message(error_code));
				LOG(LOG_DEBUG, "OUT : show_multi()");
				return;
			}

			gtk_tree_store_append(GTK_TREE_STORE(multi_store),
					      &parent_iter, NULL);
			gtk_tree_store_set(GTK_TREE_STORE(multi_store),
					   &parent_iter,
					   MULTI_TYPE_COLUMN, 0,
					   MULTI_TITLE_COLUMN, binfo->subbook_title,
					   -1);

			for(i=0 ; i < multi_count ; i ++){
				error_code = eb_multi_title(binfo->book, multi_codes[i], label);
				if(error_code  != EB_SUCCESS) {
					LOG(LOG_CRITICAL, "Failed to get multi title : %s",
						ebook_error_message(error_code));
					return;
				}
				utf_str = iconv_convert("euc-jp", "utf-8", label);

				gtk_tree_store_append(GTK_TREE_STORE(multi_store),
						      &child_iter, &parent_iter);
				gtk_tree_store_set(GTK_TREE_STORE(multi_store),
						   &child_iter,
						   MULTI_TYPE_COLUMN, 1,
						   MULTI_TITLE_COLUMN, utf_str,
						   MULTI_CODE_COLUMN, multi_codes[i],
						   MULTI_BOOK_COLUMN, binfo,
						   -1);
				g_free(utf_str);
			}


		} while (gtk_tree_model_iter_next(GTK_TREE_MODEL(dict_store), &dict_child_iter) == TRUE);

	}

	clear_candidate();
	gtk_tree_view_expand_all(GTK_TREE_VIEW(multi_view));

	LOG(LOG_DEBUG, "OUT : show_multi()");
}
