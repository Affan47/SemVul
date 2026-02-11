set_cell_for_field_value(Gtk::CellRenderer* cell, const sharedptr<const LayoutItem_Field>& field, const Gnome::Gda::Value& value)
{
  if(!field)
    return;

  if(!cell)
    return;

  const Field::glom_field_type type = field->get_glom_type();
  switch(type)
  {
    case(Field::TYPE_BOOLEAN):
    {
      Gtk::CellRendererToggle* pDerived = dynamic_cast<Gtk::CellRendererToggle*>(cell);
      if(pDerived)
        pDerived->set_active( (value.get_value_type() == G_TYPE_BOOLEAN) && value.get_boolean() );

      break;
    }
    case(Field::TYPE_IMAGE):
    {
      Gtk::CellRendererPixbuf* pDerived = dynamic_cast<Gtk::CellRendererPixbuf*>(cell);
      if(pDerived)
      {
        const Glib::RefPtr<Gdk::Pixbuf> pixbuf = Utils::get_pixbuf_for_gda_value(value);


        pDerived->property_pixbuf() = pixbuf;
      }
      else
        std::cerr << "Field::sql(): glom_type is TYPE_IMAGE but gda type is not VALUE_TYPE_BINARY" << std::endl;

      break;
    }
    default:
    {

      Gtk::CellRendererText* pDerived = dynamic_cast<Gtk::CellRendererText*>(cell);
      if(pDerived)
      {

        const Glib::ustring text = Conversions::get_text_for_gda_value(field->get_glom_type(), value, field->get_formatting_used().m_numeric_format);
        pDerived->property_text() = text;
      }
      else
      {
         std::cerr << G_STRFUNC << ": cell has an unexpected type: " << typeid(cell).name() << std::endl;
      }


      if(type == Field::TYPE_NUMERIC)
      {
        const Glib::ustring fg_color =
        field->get_formatting_used().get_text_format_color_foreground_to_use(value);
        if(!fg_color.empty())
          pDerived->property_foreground() = fg_color;
        else

          g_object_set(pDerived->gobj(), "foreground", (const char*)0, (gpointer)0);
      }

      break;
    }
  }
}
