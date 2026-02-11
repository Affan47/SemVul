TriangleSplitIteration()
{
  int numberOfChanges = 0;
  int numberOfCells = this->Mesh->GetNumberOfCells();
  for (int i=0; i<numberOfCells; i++)
    {
    if (this->Mesh->GetCellType(i) != VTK_TRIANGLE)
      {
      continue;
      }
    int test = this->TestTriangleSplit(i);
    if (test == DO_NOTHING)
      {
      continue;
      }
    this->SplitTriangle(i);
    numberOfChanges++;
    }
  return numberOfChanges;
}
