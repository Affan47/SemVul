tracksValid() const
{
    return m_tracksTime.isValid() &&
        m_tracksTime.secsTo(QDateTime::currentDateTime()) < 60 * 3;
}
