HasMetadata(vtkUnstructuredGrid *grid)
{
  int hasIt = 0;

  if (grid)
    {
    hasIt = vtkModelMetadata::HasMetadata(grid);
    }

  return hasIt;
}
