GetNumberOfNodes() const
{
  if (this->Empty())
    {
    return 0;
    }

  vtkIdType nPoints=1;
  for (int q=0; q<this->Dimension; ++q)
    {
    nPoints*=this->HiCorner[q]-this->LoCorner[q]+2;
    }
  return nPoints;
}
