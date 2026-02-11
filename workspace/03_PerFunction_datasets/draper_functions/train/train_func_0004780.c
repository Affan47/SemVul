set_column_choices(guint col, const type_vec_strings& vecStrings)
{
  InnerIgnore innerIgnore(this);

  m_ColumnTypes[col].m_choices = vecStrings;

  guint view_column_index = 0;
  bool test = get_view_column_index(col, view_column_index);
  if(test)
  {
    CellRendererList* pCellRenderer = dynamic_cast<CellRendererList*>( m_TreeView.get_column_cell_renderer(view_column_index) );
    if(pCellRenderer)
    {

      pCellRenderer->remove_all_list_items();
      for(type_vec_strings::const_iterator iter = vecStrings.begin(); iter != vecStrings.end(); ++iter)
      {
        pCellRenderer->append_list_item(*iter);
      }
    }
    else
    {

      construct_specified_columns();
    }
  }
}
