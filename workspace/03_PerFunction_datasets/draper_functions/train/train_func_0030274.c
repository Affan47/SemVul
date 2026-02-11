on_dialog_format_hide()
{
  if(!m_dialog_format || !m_context_item)
    return;

  sharedptr<LayoutItem> layout_item = m_context_item->get_layout_item();
  sharedptr<LayoutItem_Field> layout_item_field = sharedptr<LayoutItem_Field>::cast_dynamic(layout_item);
  sharedptr<LayoutItem_Text> layout_item_text = sharedptr<LayoutItem_Text>::cast_dynamic(layout_item);
  if(!layout_item_field && !layout_item_text)
    return;

  if(layout_item_field)
  {
    m_dialog_format->m_box_formatting->get_formatting(layout_item_field->m_formatting);


    layout_item_field->set_formatting_use_default(false);
  }
  else if(layout_item_text)
    m_dialog_format->m_box_formatting->get_formatting(layout_item_text->m_formatting);


  m_context_item->set_layout_item(layout_item);

  delete m_dialog_format;
  m_dialog_format = 0;
}
