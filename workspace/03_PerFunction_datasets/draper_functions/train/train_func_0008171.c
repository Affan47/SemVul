add_canvas_layout_item(const Glib::RefPtr<CanvasLayoutItem>& item)
{
  if(!item)
    return;

  CanvasEditable::add_item(item, m_items_group);
  item->raise();

#ifndef GLOM_ENABLE_CLIENT_ONLY


  item->signal_show_context().connect(
    sigc::bind(
      sigc::mem_fun(*this, &Canvas_PrintLayout::on_item_show_context_menu),
      item) );
#endif

   if(item->get_child())
     item->set_outline_visible(m_outline_visibility);

   fill_with_data_system_preferences(item, get_document());
}
