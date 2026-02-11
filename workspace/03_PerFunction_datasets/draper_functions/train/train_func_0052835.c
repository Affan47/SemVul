set_fields(const Glib::ustring& table_name, const LayoutGroup::type_list_items& fields)
{
  m_modified = false;
  m_table_name = table_name;

  Document* document = get_document();


  if(document)
  {

    m_label_table_name->set_text(table_name);


    m_model_fields->clear();
    guint field_sequence = 0;
    for(LayoutGroup::type_list_items::const_iterator iter = fields.begin(); iter != fields.end(); ++iter)
    {
      sharedptr<const LayoutItem_Field> item = sharedptr<const LayoutItem_Field>::cast_dynamic(*iter);
      if(!item)
        continue;

      Gtk::TreeModel::iterator iterTree = m_model_fields->append();
      Gtk::TreeModel::Row row = *iterTree;

      row[m_ColumnsFields.m_col_layout_item] = item;
      row[m_ColumnsFields.m_col_sequence] = field_sequence;
      ++field_sequence;
    }


  }

  m_modified = false;
}
