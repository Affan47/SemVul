Coarsen(int r)
{
  if (this->Empty())
    {
    return;
    }


  int nCells[3];
  this->GetNumberOfCells(nCells);
  for (int q=0; q<this->Dimension; ++q)
    {
    if (nCells[q]%r)
      {
      vtkGenericWarningMacro("This box cannot be coarsened.");
      return;
      }
    }

  int lo[3];
  int hi[3];
  for (int q=0; q<this->Dimension; ++q)
    {
    lo[q]=(this->LoCorner[q]<0 ? -abs(this->LoCorner[q]+1)/r-1 : this->LoCorner[q]/r);
    hi[q]=(this->HiCorner[q]<0 ? -abs(this->HiCorner[q]+1)/r-1 : this->HiCorner[q]/r);
    }
  this->SetDimensions(lo,hi);

  this->DX[0]*=r;
  this->DX[1]*=r;
  this->DX[2]*=r;
}
