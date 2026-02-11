GetNumberOfIntermediatePoints(int n)
{
  if ( n < 0 ||
       static_cast<unsigned int>(n) >= this->Internal->Nodes.size() )
    {
    return 0;
    }

  return static_cast<int>(this->Internal->Nodes[n]->Points.size());
}
