GetNumberOfArraysEnabled()
{
  int numArrays = 0;
  for(std::vector<int>::iterator i = this->Internal->ArraySettings.begin();
      i != this->Internal->ArraySettings.end(); ++i)
    {
    if(*i)
      {
      numArrays++;
      }
    }
  return numArrays;
}
