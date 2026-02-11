GetMatrix(vtkMatrix4x4 *result)
{
  double mine[16];
  this->GetMatrix(mine);
  int idx = 0;
  for (int i =0; i < 4; i++)
    {
    for(int j=0; j < 4; j++)
      {
      if (mine[idx] != *(&result->Element[i][j]))
        {
        memcpy(&result->Element[0][0], mine, 16*sizeof(double));
        result->Modified();
        return;
        }
      idx++;
      }
    }
}
