active_descendant_changed_callback(AtkObject* self, gpointer* p0)
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

        obj->on_active_descendant_changed(p0
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
        g_type_class_peek_parent(G_OBJECT_GET_CLASS(self))
    );


  if(base && base->active_descendant_changed)
    (*base->active_descendant_changed)(self, p0);
}
