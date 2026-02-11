set_current_value_vfunc(const Glib::ValueBase& value)
{
  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_interface_peek_parent(
g_type_interface_peek(G_OBJECT_GET_CLASS(gobject_), CppObjectType::get_type())
)  );

  if(base && base->set_current_value)
  {
    bool retval((*base->set_current_value)(gobj(),(value).gobj()));
    return retval;
  }

  typedef bool RType;
  return RType();
}


}
