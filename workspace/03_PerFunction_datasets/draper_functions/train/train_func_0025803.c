set_value_at(int col, int row, const Value& value)
{
  GError* gerror = 0;
  bool retvalue = gda_data_model_set_value_at(gobj(), col, row, (value).gobj(), &(gerror));
  if(gerror)
    ::Glib::Error::throw_exception(gerror);

  return retvalue;

}
