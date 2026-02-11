slotPropertyChanged()
{

    if (!m_control || !m_target)
        return;


    if (m_property.type() == QVariant::Int) {
        int intValue = m_property.read(m_target.data()).toInt();
        m_control->setValue(intValue);
    }


    else if (m_property.type() == QVariant::Double) {
        qreal realValue = m_property.read(m_target.data()).toDouble();
        int intValue = m_control->minimum() + (int)(realValue * (m_control->maximum() - m_control->minimum()));
        m_control->setValue(intValue);
    }
}
