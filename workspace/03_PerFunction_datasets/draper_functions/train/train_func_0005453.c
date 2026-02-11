import_from_model(const Glib::RefPtr<DataModel>& from, bool overwrite, GHashTable * cols_trans)
{
  GError* gerror = 0;
  bool retvalue = gda_data_model_import_from_model(gobj(), Glib::unwrap(from), static_cast<int>(overwrite), cols_trans, &(gerror));
  if(gerror)
    ::Glib::Error::throw_exception(gerror);

  return retvalue;

}
