selection_changed()
  {
    remove_button->set_sensitive(icon_tree->get_selection()->count_selected_rows() > 0);
  }
