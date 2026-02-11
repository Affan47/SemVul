make_folder(const std::string& folder_name, bool test_valid) {

  if (!test_valid || folder_name_validator.validate(folder_name).first) {

    GtkTreeIter iter;
    gtk_tree_store_append(GTK_TREE_STORE(folder_tree_store_h.get()), &iter, 0);

    gtk_tree_store_set(GTK_TREE_STORE(folder_tree_store_h.get()), &iter,
		       FolderListModelColumns::icon, folder_icon_h.get(),
		       FolderListModelColumns::name, folder_name.c_str(),


		       FolderListModelColumns::root_only, false,
		       -1);
    folder_name_validator.insert_folder_name(folder_name);

    TreePathScopedHandle path_h(gtk_tree_model_get_path(folder_tree_store_h,
							&iter));
    TreeRowRefSharedHandle row_ref_h =
      TreeRowRefSharedHandle(gtk_tree_row_reference_new(folder_tree_store_h,
							path_h));


    GobjHandle<GtkTreeModel> model_h(GTK_TREE_MODEL(gtk_list_store_new(FaxListModelColumns::cols_num,
								       G_TYPE_STRING,
								       G_TYPE_STRING,
								       G_TYPE_STRING)));
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(model_h.get()),
					 FaxListModelColumns::name,
					 list_sort_type[mode]);
    folder_row_to_fax_model_map.insert(FolderRowToFaxModelMap::value_type(row_ref_h, model_h));

    write_path();
  }
}
