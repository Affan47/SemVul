get_column_field(guint column_index) const
{
  if(column_index < m_column_items.size())
  {
    sharedptr<LayoutItem_Field> field = sharedptr<LayoutItem_Field>::cast_dynamic( m_column_items[column_index] );
    if(field)
      return field;
  }

  return sharedptr<const LayoutItem_Field>();
}
