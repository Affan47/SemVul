create_layout_get_layout()
{
  Document::type_list_layout_groups result;

  if(m_portal)
    result.push_back(m_portal);

  return result;
}
