create_table_with_default_fields(Document* document, const Glib::ustring& table_name)
{
  if(table_name.empty())
    return false;

  Glib::RefPtr<Gnome::Gda::Connection> gda_connection = get_connection();
  if(!gda_connection)
  {
    std::cerr << G_STRFUNC << ": No connection yet." << std::endl;
    return false;
  }

  bool created = false;


  sharedptr<Field> field_primary_key(new Field());
  field_primary_key->set_name(table_name + "_id");
  field_primary_key->set_title_original( Glib::ustring::compose("%1 ID", table_name) );
  field_primary_key->set_primary_key();
  field_primary_key->set_auto_increment();

  Glib::RefPtr<Gnome::Gda::Column> field_info = field_primary_key->get_field_info();
  field_info->set_allow_null(false);
  field_primary_key->set_field_info(field_info);

  field_primary_key->set_glom_type(Field::TYPE_NUMERIC);


  type_vec_fields fields;
  fields.push_back(field_primary_key);


  sharedptr<Field> field_description(new Field());
  field_description->set_name("description");
  field_description->set_title_original(_("Description"));
  field_description->set_glom_type(Field::TYPE_TEXT);
  fields.push_back(field_description);


  sharedptr<Field> field_comments(new Field());
  field_comments->set_name("comments");
  field_comments->set_title_original(_("Comments"));
  field_comments->set_glom_type(Field::TYPE_TEXT);
  field_comments->m_default_formatting.set_text_format_multiline();
  fields.push_back(field_comments);

  sharedptr<TableInfo> table_info(new TableInfo());
  table_info->set_name(table_name);
  table_info->set_title_original( Utils::title_from_string( table_name ) );

  created = create_table(table_info, fields);

  if(created)
  {

    if(document)
    {
      document->add_table(table_info);
      document->set_table_fields(table_info->get_name(), fields);
    }
  }

  return created;
}
