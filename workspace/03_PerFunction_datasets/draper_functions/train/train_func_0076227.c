removePermanentBarWidget (KHTMLViewBarWidget *barWidget)
{
  if (m_permanentBarWidget != barWidget) {
    kDebug(6050) << "no such permanent widget exists in bar";
    return;
  }

  if (!m_permanentBarWidget)
    return;

  m_permanentBarWidget->hide();
  layout()->removeWidget(m_permanentBarWidget);
  m_permanentBarWidget = 0;
}
