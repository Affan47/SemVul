get_value(TextAttribute attribute, int index)
{
  if(const char *const value = atk_text_attribute_get_value(AtkTextAttribute(int(attribute)), index))
    return Glib::ustring(value);
  else
    return Glib::ustring();
}
