create_table(const sharedptr<const TableInfo>& table_info, const Document::type_vec_fields& fields_in)
{


  bool table_creation_succeeded = false;


  Document::type_vec_fields fields = fields_in;


  if(std::find_if(fields.begin(), fields.end(), predicate_FieldHasName<Field>(GLOM_STANDARD_FIELD_LOCK)) == fields.end())
  {
    sharedptr<Field> field = sharedptr<Field>::create();
    field->set_name(GLOM_STANDARD_FIELD_LOCK);
    field->set_glom_type(Field::TYPE_TEXT);
    fields.push_back(field);
  }


  Glib::ustring sql_fields;
  for(Document::type_vec_fields::const_iterator iter = fields.begin(); iter != fields.end(); ++iter)
  {

    sharedptr<Field> field = *iter;


    Glib::RefPtr<Gnome::Gda::Column> info = field->get_field_info();
    info->set_g_type( Field::get_gda_type_for_glom_type(field->get_glom_type()) );
    field->set_field_info(info);

    Glib::ustring sql_field_description = escape_sql_id(field->get_name()) + " " + field->get_sql_type();

    if(field->get_primary_key())
      sql_field_description += " NOT NULL  PRIMARY KEY";


    if(!sql_fields.empty())
      sql_fields += ", ";

    sql_fields += sql_field_description;
  }

  if(sql_fields.empty())
  {
    std::cerr << G_STRFUNC << ": sql_fields is empty." << std::endl;
  }


  try
  {


    table_creation_succeeded = query_execute_string( "CREATE TABLE " + escape_sql_id(table_info->get_name()) + " (" + sql_fields + ");" );
    if(!table_creation_succeeded)
      std::cerr << G_STRFUNC << ": CREATE TABLE failed." << std::endl;
  }
  catch(const ExceptionConnection& ex)
  {
    std::cerr << G_STRFUNC << "CREATE TABLE failed: " << ex.what() << std::endl;
    table_creation_succeeded = false;
  }

  if(table_creation_succeeded)
  {


    if(!update_gda_metastore_for_table(table_info->get_name()))
      return false;


  }

  return table_creation_succeeded;
}
