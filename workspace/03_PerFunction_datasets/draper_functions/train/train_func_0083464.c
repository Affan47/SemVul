take_value(const Value& value)
{
  GError* gerror = 0;
  bool retvalue = gda_holder_take_value(gobj(), const_cast<GValue*>((value).gobj()), &(gerror));
  if(gerror)
    ::Glib::Error::throw_exception(gerror);

  return retvalue;

}
