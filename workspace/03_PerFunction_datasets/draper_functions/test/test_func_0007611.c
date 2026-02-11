set_rules_visibility(bool visible)
{
  if(m_grid_rules_group)
    m_grid_rules_group->property_visibility() = (visible ? Goocanvas::ITEM_VISIBLE : Goocanvas::ITEM_INVISIBLE);
  else
    std::cerr << G_STRFUNC << ": m_grid_rules_group was null." << std::endl;


  if(m_grid_lines && m_grid_rules_group)
    m_grid_lines->lower(m_grid_rules_group);
}
