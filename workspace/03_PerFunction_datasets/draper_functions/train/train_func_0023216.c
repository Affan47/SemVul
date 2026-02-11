on_button_down()
{
  Glib::RefPtr<Gtk::TreeView::Selection> refSelection = m_treeview_fields->get_selection();
  if(refSelection)
  {
    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {
      Gtk::TreeModel::iterator iterNext = iter;
      iterNext++;

      Gtk::TreeModel::iterator parent = iter->parent();
      bool is_last = false;
      if(parent)
        is_last = (iterNext == parent->children().end());
      else
        is_last = (iterNext == m_model_items->children().end());

      if(!is_last)
      {

        m_model_items->iter_swap(iter, iterNext);

        m_modified = true;
      }
    }

  }

  enable_buttons();
}
