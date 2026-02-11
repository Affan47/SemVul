ui_show_modification_status()
{
  const bool modified = m_pDocument->get_modified();


  if(m_action_save)
    m_action_save->set_sensitive(modified);

  if(m_action_saveas)
    m_action_saveas->set_sensitive(modified);
}
