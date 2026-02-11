show_context_menu(GdkEventButton *event)
{
  std::cout << "ComboAsRadioButtons::show_context_menu()" << std::endl;
  AppWindow* pApp = get_appwindow();
  if(pApp)
  {


    pApp->add_developer_action(m_refContextLayout);
    pApp->add_developer_action(m_refContextAddField);
    pApp->add_developer_action(m_refContextAddRelatedRecords);
    pApp->add_developer_action(m_refContextAddGroup);

    pApp->update_userlevel_ui();


    if(pApp->get_userlevel() == AppState::USERLEVEL_DEVELOPER)
    {
      GdkModifierType mods;
      gdk_window_get_device_position( gtk_widget_get_window (Gtk::Widget::gobj()), event->device, 0, 0, &mods );
      if(mods & GDK_BUTTON3_MASK)
      {

        m_pMenuPopup->popup(event->button, event->time);
      }
    }
  }
}
