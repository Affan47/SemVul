Regler_signal_value_entry_callback(GxRegler* self, GdkRectangle* p0,GdkEventButton* p1,void* data)
{
  using namespace Gxw;
  typedef sigc::slot< bool,const Gdk::Rectangle&,GdkEventButton* > SlotType;


  if(Glib::ObjectBase::_get_current_wrapper((GObject*) self))
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
    #endif
      if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
        return static_cast<int>((*static_cast<SlotType*>(slot))(Glib::wrap(p0)
, p1));
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
    #endif
  }

  typedef gboolean RType;
  return RType();
}
