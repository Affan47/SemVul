on_calendar_button_press_event(GdkEventButton *event)
{
#ifndef GLOM_ENABLE_CLIENT_ONLY


  AppWindow* pApp = get_appwindow();
  if(pApp)
  {
    pApp->add_developer_action(m_refContextLayout);
    pApp->update_userlevel_ui();
  }
#endif

  GdkModifierType mods;
  gdk_window_get_device_position( gtk_widget_get_window(Gtk::Widget::gobj()), event->device, 0, 0, &mods );
  if(mods & GDK_BUTTON3_MASK)
  {

    m_pMenuPopup->popup(event->button, event->time);
    return;
  }
  else
  {
    if(event->type == GDK_2BUTTON_PRESS)
    {


      return;
    }
  }

  return;
}
