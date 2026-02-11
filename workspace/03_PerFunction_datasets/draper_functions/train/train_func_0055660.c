set_choices_related(const Document* document, const sharedptr<const LayoutItem_Field>& layout_field, const Gnome::Gda::Value& foreign_key_value)
{
  if(!document)
  {
    std::cerr << G_STRFUNC << ": document is null." << std::endl;
    return;
  }

  const Formatting& format = layout_field->get_formatting_used();
  sharedptr<const Relationship> choice_relationship;
  sharedptr<const LayoutItem_Field> layout_choice_first;
  sharedptr<const LayoutGroup> layout_choice_extra;
  Formatting::type_list_sort_fields choice_sort_fields;
  bool choice_show_all = false;
  format.get_choices_related(choice_relationship, layout_choice_first, layout_choice_extra, choice_sort_fields, choice_show_all);
  if(layout_choice_first->get_glom_type() == Field::TYPE_INVALID)
    std::cerr << G_STRFUNC << ": layout_choice_first has invalid type. field name: " << layout_choice_first->get_name() << std::endl;


  sharedptr<LayoutGroup> layout_choice_extra_full = glom_sharedptr_clone(layout_choice_extra);
  const Glib::ustring table_name = choice_relationship->get_to_table();
  document->fill_layout_field_details(table_name,  layout_choice_extra_full);


  LayoutGroup::type_list_items extra_fields;
  if(layout_choice_extra_full)
    extra_fields = layout_choice_extra_full->get_items_recursive();

  LayoutGroup::type_list_const_items layout_items;
  layout_items.push_back(layout_choice_first);
  layout_items.insert(layout_items.end(), extra_fields.begin(), extra_fields.end());


  layout_items = Utils::get_layout_items_plus_primary_key(layout_items, document, table_name);


  const Glib::ustring to_table = choice_relationship->get_to_table();
  FoundSet found_set;
  found_set.m_table_name = to_table;

  if(!foreign_key_value.is_null())
  {
    const sharedptr<const Field> to_field = document->get_field(to_table, choice_relationship->get_to_field());

    found_set.m_where_clause = Utils::build_simple_where_expression(
      to_table, to_field, foreign_key_value);
  }

  found_set.m_sort_clause = choice_sort_fields;
  if(found_set.m_sort_clause.empty())
  {

    found_set.m_sort_clause.push_back( FoundSet::type_pair_sort_field(layout_choice_first, true ) );
  }

  m_db_layout_items.clear();


  const Privileges table_privs = Privs::get_current_privs(found_set.m_table_name);
  m_refModel = DbTreeModelWithExtraText::create(found_set, layout_items, table_privs.m_view, false , m_db_layout_items);
  if(!m_refModel)
  {
    std::cerr << G_STRFUNC << ": DbTreeModel::create() returned a null model." << std::endl;
  }


}
