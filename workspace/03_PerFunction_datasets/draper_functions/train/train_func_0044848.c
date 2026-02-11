showConnectionInformation() const
{
   m_pConnectionInformation->show();

   if (!m_pConnectionInformation->isActiveWindow())
   {
      m_pConnectionInformation->activateWindow();
      m_pConnectionInformation->raise();
   }
}
