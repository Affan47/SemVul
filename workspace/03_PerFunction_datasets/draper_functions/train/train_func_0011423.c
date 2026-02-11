readPppSettings(const PppSettings& pppSettings) const
{
   if (!pppSettings.refuseEap())
   {
      m_Widget.m_pPppAllowProtocolsRadioButton->setChecked(false);
      m_Widget.m_pPppUseEAPRadioButton->setChecked(true);
      m_Widget.m_pPppAllowProtocolsListWidget->setEnabled(false);
      m_Widget.m_pPppPropertiesButton->setEnabled(true);
      m_Widget.m_pPppUserNameEdit->setEnabled(false);
      m_Widget.m_pPppPwdEdit->setEnabled(false);
   }
   else
   {
      m_Widget.m_pPppAllowProtocolsRadioButton->setChecked(true);
      m_Widget.m_pPppUseEAPRadioButton->setChecked(false);
      m_Widget.m_pPppAllowProtocolsListWidget->setEnabled(true);
      m_Widget.m_pPppPropertiesButton->setEnabled(false);
      m_Widget.m_pPppUserNameEdit->setEnabled(true);
      m_Widget.m_pPppPwdEdit->setEnabled(true);
   }

   m_Widget.m_pPppAllowProtocolsListWidget->item(0)->setCheckState(!pppSettings.refusePap() ? Qt::Checked : Qt::Unchecked);
   m_Widget.m_pPppAllowProtocolsListWidget->item(1)->setCheckState(!pppSettings.refuseChap() ? Qt::Checked : Qt::Unchecked);
   m_Widget.m_pPppAllowProtocolsListWidget->item(2)->setCheckState(!pppSettings.refuseMsChap() ? Qt::Checked : Qt::Unchecked);
   m_Widget.m_pPppAllowProtocolsListWidget->item(3)->setCheckState(!pppSettings.refuseMsChapV2() ? Qt::Checked : Qt::Unchecked);

   m_Widget.m_pPppUserNameEdit->setText(pppSettings.userName());
   m_Widget.m_pPppPwdEdit->setText(pppSettings.password());
}
