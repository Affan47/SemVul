communicateWith(const Country* otherCountry) const
{
  if (!otherCountry)
  {
    kDebug() << "OUT otherCountry null Country::communicateWith" << endl;
    return false;
  }


  if (otherCountry == this) {return true;}


  unsigned int nbNeighbours = neighbours().size();
  for (unsigned int i = 0; i < nbNeighbours; i++)
  {
    if (neighbours().at(i) == otherCountry)
    {

      return true;
    }
  }

  return false;
}
