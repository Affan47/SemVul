on_canvas_selection_changed()
{
  Canvas_PrintLayout::type_vec_items items = m_canvas.get_selected_items();


  m_layout_items_selected.clear();
  for(type_vec_connections::iterator iter = m_connections_items_selected_moved.begin();
    iter != m_connections_items_selected_moved.end(); ++iter)
  {
    iter->disconnect();
  }
  m_connections_items_selected_moved.clear();


  for(Canvas_PrintLayout::type_vec_items::const_iterator iter = items.begin();
    iter != items.end(); ++iter)
  {
    Glib::RefPtr<CanvasLayoutItem> item = Glib::RefPtr<CanvasLayoutItem>::cast_dynamic(*iter);
    if(!item)
      continue;


    m_layout_items_selected.push_back(item);
    m_connections_items_selected_moved.push_back(
      item->signal_moved().connect(
        sigc::mem_fun(*this, &Window_PrintLayout_Edit::on_selected_item_moved)));
  }

  double x = 0;
  double y = 0;
  double width = 0;
  double height = 0;
  get_dimensions_of_multiple_selected_items(x, y, width, height);


  const bool old_ignore = m_ignore_spinbutton_signals;
  m_ignore_spinbutton_signals = true;
  m_spinbutton_x->set_value(x);
  m_spinbutton_y->set_value(y);
  m_spinbutton_width->set_value(width);
  m_spinbutton_height->set_value(height);
  m_ignore_spinbutton_signals = old_ignore;


  const bool one_selected = (m_layout_items_selected.size() == 1);
  const bool some_selected = !m_layout_items_selected.empty();


  m_box_item_position->set_sensitive(some_selected);
  m_spinbutton_x->set_sensitive(some_selected);
  m_spinbutton_y->set_sensitive(some_selected);
  m_spinbutton_width->set_sensitive(one_selected);
  m_spinbutton_height->set_sensitive(one_selected);

  if(m_action_edit_cut)
    m_action_edit_cut->set_sensitive(some_selected);

  if(m_action_edit_copy)
    m_action_edit_copy->set_sensitive(some_selected);

  if(m_action_edit_delete)
    m_action_edit_delete->set_sensitive(some_selected);
}
