get_conversion_possible(glom_field_type field_type_src, glom_field_type field_type_dest)
{
  type_map_conversions::const_iterator iterFind = m_map_conversions.find(field_type_src);
  if(iterFind != m_map_conversions.end())
  {
    const type_list_conversion_targets list_conversions = iterFind->second;
    type_list_conversion_targets::const_iterator iterConversionFind = std::find(list_conversions.begin(), list_conversions.end(), field_type_dest);
    if(iterConversionFind != list_conversions.end())
      return true;
  }

  return false;
}
