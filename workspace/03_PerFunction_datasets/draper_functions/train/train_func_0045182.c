get_uri_vfunc_callback(AtkHyperlink* self, gint i)
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

        return obj->get_uri_vfunc(i
);
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
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(self))
  );


  if(base && base->get_uri)
  {
    gchar* retval = (*base->get_uri)(self, i);
    return retval;
  }


  typedef gchar* RType;
  return RType();
}
