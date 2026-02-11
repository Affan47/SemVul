on_checkbox_toggled(int id, CheckButton* cbox)
{
  m_pConfig->setOverride(id, cbox->get_active() ? true : false);


  if(cbox->getName() != NULL)
  {
    ModWidget* widget = NULL;

    m_refGlade->get_widget(cbox->getName(), widget);

    if(widget)
    {
      ((ModWidget*)widget)->reload();
    }
  }

}
