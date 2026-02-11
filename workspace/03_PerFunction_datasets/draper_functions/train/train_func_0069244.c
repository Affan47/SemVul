fullPatientName(const QString &uuid) const
{
    return m_Model->patientName(QStringList() << uuid);
}
