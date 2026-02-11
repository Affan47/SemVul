vtkIsPermutationMatrix(vtkMatrix4x4 *matrix)
{
  for (int i = 0; i < 3; i++)
    {
    if (matrix->GetElement(3,i) != 0)
      {
      return 0;
      }
    }
  if (matrix->GetElement(3,3) != 1)
    {
    return 0;
    }
  for (int j = 0; j < 3; j++)
    {
    int k = 0;
    for (int i = 0; i < 3; i++)
      {
      if (matrix->GetElement(i,j) != 0)
        {
        k++;
        }
      }
    if (k != 1)
      {
      return 0;
      }
    }
  return 1;
}
