enable_buttons()
{

  Glib::RefPtr<Gtk::TreeView::Selection> refSelection = m_treeview_fields->get_selection();
  if(refSelection)
  {
    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {

      bool enable_up = true;
      Gtk::TreeModel::iterator iterParent = iter->parent();
      if(iterParent)
      {

        if(iter == iterParent->children().begin())
          enable_up = false;
      }
      else
      {

        if(iter == m_model_items->children().begin())
          enable_up = false;
      }

      m_button_up->set_sensitive(enable_up);


      Gtk::TreeModel::iterator iterNext = iter;
      iterNext++;

      bool enable_down = true;
      if(iterParent)
      {

        if(iterNext == iterParent->children().end())
          enable_down = false;
      }
      else
      {

        if(iterNext == m_model_items->children().end())
          enable_down = false;
      }

      m_button_down->set_sensitive(enable_down);

      m_button_field_delete->set_sensitive(true);


      sharedptr<LayoutItem> layout_item = (*iter)[m_model_items->m_columns.m_col_layout_item];
      sharedptr<LayoutItem_WithFormatting> layoutitem_withformatting = sharedptr<LayoutItem_WithFormatting>::cast_dynamic(layout_item);
      const bool is_field = layoutitem_withformatting;
      m_button_formatting->set_sensitive(is_field);
    }
    else
    {

      m_button_down->set_sensitive(false);
      m_button_up->set_sensitive(false);
      m_button_field_delete->set_sensitive(false);
      m_button_formatting->set_sensitive(false);
    }
  }

}
