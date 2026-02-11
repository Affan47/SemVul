countryAt(const QPointF& point)
{

    QPointF norm = point;
    if ( norm.x() < 0 || norm.x() >= m_countriesMask.width()
      || norm.y() < 0 || norm.y() >= m_countriesMask.height() )
      return 0;

    int index = qBlue(m_countriesMask.pixel(norm.toPoint()));

    if (index >= m_countries.size()) return 0;
    return m_countries.at(index);
}
