get_suitable_field_width_for_widget(Gtk::Widget& widget, const sharedptr<const LayoutItem_Field>& field_layout, bool or_title, bool for_treeview)
{
  int result = 150;

  const Field::glom_field_type field_type = field_layout->get_glom_type();

  Glib::ustring example_text;
  switch(field_type)
  {
    case(Field::TYPE_DATE):
    {
      const Glib::Date date(31, Glib::Date::Month(12), 2000);
      example_text = Conversions::get_text_for_gda_value(field_type, Gnome::Gda::Value(date));
      break;
    }
    case(Field::TYPE_TIME):
    {
      Gnome::Gda::Time time = {0, 0, 0, 0, 0};
      time.hour = 24;
      time.minute = 59;
      time.second = 59;
      example_text = Conversions::get_text_for_gda_value(field_type, Gnome::Gda::Value(time));
      break;
    }
    case(Field::TYPE_NUMERIC):
    {
      if(for_treeview)
        example_text = "EUR 999.99";
      else
        example_text = "EUR 9999999999";

      break;
    }
    case(Field::TYPE_TEXT):
    case(Field::TYPE_IMAGE):
    {
      if(for_treeview)
        example_text = "AAAAAAAAAAAA";
      else
        example_text = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

      break;
    }
    default:
    {
      break;
    }
  }

  if(!example_text.empty())
  {

    result = get_width_for_text(widget, example_text);
  }

  if(or_title)
  {

    const int title_width = get_width_for_text(widget, item_get_title(field_layout));
    if(title_width > result)
      result = title_width;
  }

  return result;
}
