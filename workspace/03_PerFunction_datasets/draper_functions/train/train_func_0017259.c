CreateThickArrow(vtkPoints *pts, vtkCellArray *lines,
                                         vtkCellArray *polys, vtkUnsignedCharArray *colors)
{
  vtkIdType ptIds[8];

  ptIds[0] = pts->InsertNextPoint( -0.5, -0.1, 0.0);
  ptIds[1] = pts->InsertNextPoint(  0.1, -0.1, 0.0);
  ptIds[2] = pts->InsertNextPoint(  0.1, -0.2, 0.0);
  ptIds[3] = pts->InsertNextPoint(  0.5,  0.0, 0.0);
  ptIds[4] = pts->InsertNextPoint(  0.1,  0.2, 0.0);
  ptIds[5] = pts->InsertNextPoint(  0.1,  0.1, 0.0);
  ptIds[6] = pts->InsertNextPoint( -0.5,  0.1, 0.0);

  if ( this->Filled )
    {
    polys->InsertNextCell(4);
    polys->InsertCellPoint(ptIds[0]);
    polys->InsertCellPoint(ptIds[1]);
    polys->InsertCellPoint(ptIds[5]);
    polys->InsertCellPoint(ptIds[6]);
    colors->InsertNextValue(this->RGB[0]);
    colors->InsertNextValue(this->RGB[1]);
    colors->InsertNextValue(this->RGB[2]);

    polys->InsertNextCell(5,ptIds+1);
    colors->InsertNextValue(this->RGB[0]);
    colors->InsertNextValue(this->RGB[1]);
    colors->InsertNextValue(this->RGB[2]);
    }
  else
    {
    ptIds[7] = ptIds[0];
    lines->InsertNextCell(8,ptIds);
    colors->InsertNextValue(this->RGB[0]);
    colors->InsertNextValue(this->RGB[1]);
    colors->InsertNextValue(this->RGB[2]);
    }
}
