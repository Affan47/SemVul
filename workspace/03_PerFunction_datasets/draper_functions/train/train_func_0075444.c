statement_execute_non_select(const Glib::RefPtr<const Statement>& cmd, const Glib::RefPtr<const Set>& params)
{
  GError* gerror = 0;
  const int retval = gda_connection_statement_execute_non_select(gobj(), const_cast<GdaStatement*>(Glib::unwrap(cmd)),  const_cast<GdaSet*>(Glib::unwrap(params)), 0, &gerror);

  if(gerror)
    ::Glib::Error::throw_exception(gerror);

  return retval;
}
