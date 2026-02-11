format_value_callback(GxRegler* self, gdouble p0)
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

        return (strlen(obj->on_format_value(p0
).c_str()) ? g_strdup(obj->on_format_value(p0
).c_str()) : 0);
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


  if(base && base->format_value)
    return (*base->format_value)(self, p0);

  typedef gchar* RType;
  return RType();
}
