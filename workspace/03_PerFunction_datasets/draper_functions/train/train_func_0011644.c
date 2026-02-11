FixPoints()
{
  vtkDebugMacro(<< "In FixPoints..." << endl);

  for (int j = this->CellOffset; j < this->NumberOfCells + this->CellOffset; j++ )
    {
    int *conns = this->OrigConnections + (j * this->PointsPerCell);


    for (int k = 0; k < this->PointsPerCell; k++)
      {
      if  ((conns[k] <= 0) || (conns[k] > this->NumberOfPoints))
        {
        for (int m = 0; m < this->PointsPerCell; m++)
          {
          conns[m] = 0;
          }
        break;
        }
      }

    if (this->DoBugFix)
      {

      int lastk = this->PointsPerCell-1;
      const double thresh = .06981317007977;
      for (int k = 0; k < this->PointsPerCell; k++)
        {
        double ydiff = abs(this->PointY[conns[k]]
                           - this->PointY[conns[lastk]]);

        if (ydiff > thresh)
          {
          for (int m = 0; m < this->PointsPerCell; m++)
            {
            conns[m] = 0;
            }
          break;
          }
        }
      }
    }
  vtkDebugMacro(<< "Leaving FixPoints..." << endl);
}
