get_model_column_index(guint view_column_index, guint& model_column_index)
{

  model_column_index = 0;

  const guint hidden = get_count_hidden_system_columns();
  const guint count = m_ColumnTypes.size();
  if(hidden > count)
    return false;

  if(view_column_index >=  (count - hidden))
    return false;

  model_column_index = view_column_index + hidden;

  return true;
}
