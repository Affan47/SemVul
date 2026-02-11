SetCells(int type, vtkCellArray *cells)
{
  int *types = new int [cells->GetNumberOfCells()];
  for (vtkIdType i = 0; i < cells->GetNumberOfCells(); i++)
    {
    types[i] = type;
    }

  this->SetCells(types, cells);

  delete [] types;
}
