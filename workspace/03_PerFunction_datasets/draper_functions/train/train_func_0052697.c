get_field(const sharedptr<const LayoutItem_Field>& layout_item, bool include_item)
{
  type_list_widgets result;

  get_direct_fields(m_listFields.begin(), m_listFields.end(), std::back_inserter(result), layout_item, include_item);


  for(type_sub_flow_tables::const_iterator iter = m_sub_flow_tables.begin(); iter != m_sub_flow_tables.end(); ++iter)
  {
    FlowTableWithFields* subtable = *iter;
    if(subtable)
    {
      type_list_widgets sub_list = subtable->get_field(layout_item, include_item);
      if(!sub_list.empty())
      {

        result.insert(result.end(), sub_list.begin(), sub_list.end());
      }
    }
  }

  return result;
}
