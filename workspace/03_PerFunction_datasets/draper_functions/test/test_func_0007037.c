get_position_vfunc_callback(AtkComponent* self, gint* x, gint* y, AtkCoordType coord_type)
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

        obj->get_position_vfunc(*(x)
, *(y)
, ((CoordType)(coord_type))
);
        return;
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


  if(base && base->get_position)
  {
    (*base->get_position)(self, x, y, coord_type);
  }

}
