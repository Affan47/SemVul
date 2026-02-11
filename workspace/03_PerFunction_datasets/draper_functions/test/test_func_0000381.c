move_selected_faxes_to_trash_folder(void) {


  GtkTreeIter trash_iter;
  TreePathScopedHandle trash_path_h(gtk_tree_row_reference_get_path(trash_row_ref_h));
  if (trash_path_h.get() &&
      gtk_tree_model_get_iter(folder_tree_store_h, &trash_iter, trash_path_h)) {


    SelectedRowsHandle rows_handle(fax_tree_view_p);

    rows_handle.get_ref_list(gtk_tree_view_get_model(fax_tree_view_p),
			     fax_drag_source_row_refs);


    move_fax(&trash_iter);
  }
  else write_error("Selection error in FaxListManager::move_selected_fax_to_trash_folder()\n");
}
