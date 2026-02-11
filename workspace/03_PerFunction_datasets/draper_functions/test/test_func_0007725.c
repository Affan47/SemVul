set_design_mode(bool value)
{
#ifndef GLOM_ENABLE_CLIENT_ONLY
  FlowTable::set_design_mode(value);
#else
  FlowTable::set_design_mode(value);
#endif


  for(type_sub_flow_tables::iterator iter = m_sub_flow_tables.begin(); iter != m_sub_flow_tables.end(); ++iter)
  {
    FlowTableWithFields* subtable = *iter;
    if(subtable)
      subtable->set_design_mode(value);
  }
}
