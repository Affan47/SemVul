ref_at_vfunc_callback(AtkTable* self, gint row, gint column)
{
  Glib::ObjectBase *const obj_base = static_cast<Glib::ObjectBase*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));


  if(obj_base && obj_base->is_derived_())
  {
    CppObjectType *const obj = dynamic_cast<CppObjectType* const>(obj_base);
    if(obj)
    {
      #ifdef GLIBMM_EXCEPTIONS_ENABLED
      try
      {
      #endif

        return Glib::unwrap_copy(obj->get_at_vfunc(row
, column
));
      #ifdef GLIBMM_EXCEPTIONS_ENABLED
      }
      catch(...)
      {
        Glib::exception_handlers_invoke();
      }
      #endif
    }
  }

  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_interface_peek_parent(
g_type_interface_peek(G_OBJECT_GET_CLASS(self), CppObjectType::get_type())
)  );


  if(base && base->ref_at)
  {
    AtkObject* retval = (*base->ref_at)(self, row, column);
    return retval;
  }


  typedef AtkObject* RType;
  return RType();
}
