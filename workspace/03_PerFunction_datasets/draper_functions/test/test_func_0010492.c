RISK_GetAdjCountryOfCountry(int iCountry, int j)
{
  Country* country = m_world->getCountries().at(iCountry);
  if (j >= country->neighbours().size())
  {
    return -1;
  }
  Country* neighbour = country->neighbours()[j];
  for (int i=0; i<m_world->getCountries().size(); i++)
  {
    if (m_world->getCountries().at(i) == neighbour)
    {
      return i;
    }
  }
  return -1;
}
