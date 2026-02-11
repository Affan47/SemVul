check_structure() const
{
  GError* gerror = 0;
  bool retvalue = gda_sql_statement_check_structure(const_cast<GdaSqlStatement*>(gobj()), &(gerror));
  if(gerror)
    ::Glib::Error::throw_exception(gerror);

  return retvalue;

}
