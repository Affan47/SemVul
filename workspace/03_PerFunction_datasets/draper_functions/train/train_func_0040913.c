ReadCellProperties(double *cellProperties,
                                       const vtkIdType& numCells,
                                       const vtkIdType& numPropertiesInCell)
{
  double *cell = cellProperties;
  for(vtkIdType i=0;i<numCells;++i)
    {
    this->CellProperties->AddCellInfo(cell);
    cell += numPropertiesInCell;
    }
}
