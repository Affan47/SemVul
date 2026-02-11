centralwidgetSet(QWidget * widget)
{
    m_pCentral = widget;
    if (m_containerPtr)
        m_containerPtr->applianceSetCentralwidget(m_pCentral.data());
}
