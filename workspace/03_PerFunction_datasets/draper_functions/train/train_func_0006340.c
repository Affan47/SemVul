build_sql_select_count_rows(const Glib::RefPtr<const Gnome::Gda::SqlBuilder>& sql_query)
{
  Glib::RefPtr<Gnome::Gda::SqlBuilder> result;

  if(!sql_query)
  {
    std::cerr << G_STRFUNC << ": sql_query was null." << std::endl;
    return result;
  }

  result = Gnome::Gda::SqlBuilder::create(Gnome::Gda::SQL_STATEMENT_SELECT);


  const guint target_id = result->add_sub_select( sql_query->get_sql_statement() );
  result->select_add_target_id(target_id, "glomarbitraryalias");

  const Gnome::Gda::SqlBuilder::Id id_function = result->add_function("COUNT", result->add_id("*"));
  result->add_field_value_id(id_function);

  return result;
}
