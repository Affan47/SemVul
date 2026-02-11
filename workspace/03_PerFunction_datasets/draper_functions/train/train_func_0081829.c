storableData() const
{
    return QString("%1;;%2")
            .arg(m_Measurement->m_value->value())
            .arg(selectedUnitUuid());
}
