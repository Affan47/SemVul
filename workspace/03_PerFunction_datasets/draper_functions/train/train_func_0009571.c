set_value_str(const Glib::RefPtr<DataHandler>& dh, const Glib::ustring& value)
{
  GError* gerror = 0;
  bool retvalue = gda_holder_set_value_str(gobj(), Glib::unwrap(dh), value.c_str(), &(gerror));
  if(gerror)
    ::Glib::Error::throw_exception(gerror);

  return retvalue;

}
