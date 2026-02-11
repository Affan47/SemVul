DbTreeModelWithExtraText(const FoundSet& found_set, const type_vec_const_layout_items& layout_items, bool get_records, bool find_mode, Base_DB::type_vecConstLayoutFields& fields_shown)
: Glib::ObjectBase( typeid(DbTreeModel) ),
  DbTreeModel(found_set, layout_items, get_records, find_mode, fields_shown),
  m_column_index_first(-1)
{

  int column_index = 0;
  for(type_vec_const_layout_items::const_iterator iter = layout_items.begin(); iter != layout_items.end(); ++iter)
  {
    const sharedptr<const LayoutItem_Field> item_field =
      sharedptr<const LayoutItem_Field>::cast_dynamic(*iter);
    if(item_field)
    {
      m_item_first = item_field;
      break;
    }

    ++column_index;
  }


  if(m_item_first)
  {
   m_column_index_first = column_index;
  }
  else
  {
    std::cerr << G_STRFUNC << ": The first field was found in the list." << std::endl;
  }
}
