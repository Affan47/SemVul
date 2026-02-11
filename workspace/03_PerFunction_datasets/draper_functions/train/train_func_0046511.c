equal(const Glib::RefPtr<const Column>& src) const
{
  if(!src)
    return false;

  const bool result = get_description() == src->get_description() &&
                get_name() == src->get_name() &&
                get_dbms_type() == src->get_dbms_type() &&
                get_g_type() == src->get_g_type() &&
                get_allow_null() == src->get_allow_null() &&
                get_auto_increment() == src->get_auto_increment() &&
                get_position() == src->get_position() &&
                get_default_value() == src->get_default_value();

  return result;
}
