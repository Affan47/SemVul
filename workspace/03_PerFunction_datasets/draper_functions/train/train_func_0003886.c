GetNumberOfCells()
{
  vtkIdType tmp=0;
  for ( int c=0; c<LSDynaMetaData::NUM_CELL_TYPES; ++c )
    {
    tmp += this->P->NumberOfCells[c];
    }
  return tmp;
}
