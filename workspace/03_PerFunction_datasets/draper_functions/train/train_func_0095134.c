putArmiesInto(int nb, int country)
{
  kDebug() << nb << country << m_distributionData[country];
  if (nb > m_distributionData.nbToPlace())
  {
    kError() << "Removing " << nb << " armies while owning " << m_distributionData.nbToPlace() << endl;
    exit(1);
  }
  m_distributionData.setNbToPlace(m_distributionData.nbToPlace() - nb);
  m_distributionData[country] = m_distributionData[country] + nb;
}
