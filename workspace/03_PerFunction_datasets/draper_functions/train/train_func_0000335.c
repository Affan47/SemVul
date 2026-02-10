BuildCursorGeometryWithoutHole()
{
  this->ComputeAxes();

  double bounds[6];
  this->Image->GetBounds(bounds);


  const double pdLength = 20 * 0.5 * sqrt(
    (bounds[1] - bounds[0])*(bounds[1] - bounds[0]) +
    (bounds[3] - bounds[2])*(bounds[3] - bounds[2]) +
    (bounds[5] - bounds[4])*(bounds[5] - bounds[4]));


  double pts[6][3];
  for (int i = 0; i < 3; i++)
    {
    pts[0][i] = this->Center[i] - pdLength * this->XAxis[i];
    pts[1][i] = this->Center[i] + pdLength * this->XAxis[i];
    pts[2][i] = this->Center[i] - pdLength * this->YAxis[i];
    pts[3][i] = this->Center[i] + pdLength * this->YAxis[i];
    pts[4][i] = this->Center[i] - pdLength * this->ZAxis[i];
    pts[5][i] = this->Center[i] + pdLength * this->ZAxis[i];
    }

  for (int j = 0; j < 3; j++)
    {
    vtkPoints *centerlinePoints = this->CenterlineAxis[j]->GetPoints();
    centerlinePoints->SetPoint(0, pts[2*j]);
    centerlinePoints->SetPoint(1, pts[2*j+1]);

    this->CenterlineAxis[j]->Modified();
    }

  this->PolyDataBuildTime.Modified();
}
