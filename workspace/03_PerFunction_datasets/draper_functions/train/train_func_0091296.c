operator==(const LayoutItem_Field& src) const
{
  bool result = LayoutItem_WithFormatting::operator==(src) &&
    UsesRelationship::operator==(src) &&
    (m_priv_view == src.m_priv_view) &&
    (m_priv_edit == src.m_priv_edit) &&
    (m_hidden == src.m_hidden) &&
    (m_formatting_use_default == src.m_formatting_use_default) &&
    (m_field_cache_valid == src.m_field_cache_valid);

  if(m_field && src.m_field)
    result = result && (*m_field == *(src.m_field));
  else
    result = result && (m_field == src.m_field);

  if(m_title_custom && src.m_title_custom)
    result = result && (*m_title_custom == *(src.m_title_custom));
  else
    result = result && (m_title_custom == src.m_title_custom);

  return result;
}
