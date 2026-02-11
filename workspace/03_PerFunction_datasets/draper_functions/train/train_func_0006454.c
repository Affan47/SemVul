onUpdateStatistic() const
{
   const NetworkInterface::Statistic statistic(NetworkInterface::statistic(m_strInterfaceName.toStdString()));

   m_Widget.m_pTransmittedBytes->setText(InterfaceStatisticsDialog::formatBytes(statistic.transmitted().bytes()));
   m_Widget.m_pTransmittedPackets->setText(QString::number(statistic.transmitted().packets()));
   m_Widget.m_pTransmissionErrors->setText(QString::number(statistic.transmitted().errs()));
   m_Widget.m_pCollisions->setText(QString::number(statistic.transmitted().colls()));

   m_Widget.m_pReceivedBytes->setText(InterfaceStatisticsDialog::formatBytes(statistic.received().bytes()));
   m_Widget.m_pReceivedPackets->setText(QString::number(statistic.received().packets()));
   m_Widget.m_pReceptionErrors->setText(QString::number(statistic.received().errs()));

   m_Widget.m_pConnectionTime->setText(connectionTime());
}
