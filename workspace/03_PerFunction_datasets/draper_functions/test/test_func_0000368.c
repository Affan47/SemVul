get_value_selected(guint col)
{
  Glib::ustring strValue = get_value(get_item_selected(), col);
  return strValue;
}
