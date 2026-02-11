get_sub_flowtables_max_columns() const
{
  guint result = get_lines();

  for(type_sub_flow_tables::const_iterator iter = m_sub_flow_tables.begin(); iter != m_sub_flow_tables.end(); ++iter)
  {
    const FlowTableWithFields* subtable = *iter;
    if(subtable)
    {
      const guint count = subtable->get_lines();
      if(count > result)
          result = count;
    }
  }

  return result;
}
