get_fixed_cell_height()
{
  if(m_fixed_cell_height <= 0)
  {


    Glib::RefPtr<Pango::Layout> refLayout = m_TreeView.create_pango_layout("ExampleEg");
    int width = 0;
    int height = 0;
    refLayout->get_pixel_size(width, height);
    m_fixed_cell_height = height;


    for(type_column_items::iterator iter = m_column_items.begin(); iter != m_column_items.end(); ++iter)
    {
      Glib::ustring font_name;

      sharedptr<const LayoutItem_WithFormatting> item_withformatting = sharedptr<const LayoutItem_WithFormatting>::cast_dynamic(*iter);
      if(item_withformatting)
      {
         const Formatting& formatting = item_withformatting->get_formatting_used();
         font_name = formatting.get_text_format_font();
      }

      if(font_name.empty())
        continue;


      Glib::RefPtr<Pango::Layout> refLayout = m_TreeView.create_pango_layout(_("ExampleEg"));
      const Pango::FontDescription font(font_name);
      refLayout->set_font_description(font);
      int width = 0;
      int height = 0;
      refLayout->get_pixel_size(width, height);

      if(height > (int)m_fixed_cell_height)
        m_fixed_cell_height = (guint)height;
    }
  }


  int extra_height = 0;
  gtk_widget_style_get(GTK_WIDGET(m_TreeView.gobj()), "vertical-separator", &extra_height, (void*)0);


  return m_fixed_cell_height + extra_height;
}
