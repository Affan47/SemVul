CreateCross(vtkPoints *pts, vtkCellArray *lines,
                                   vtkCellArray *polys, vtkUnsignedCharArray *colors,
                                   double scale)
{
  vtkIdType ptIds[4];

  if ( this->Filled )
    {
    this->CreateThickCross(pts,lines,polys,colors);
    }
  else
    {
    ptIds[0] = pts->InsertNextPoint(-0.5*scale, 0.0, 0.0);
    ptIds[1] = pts->InsertNextPoint( 0.5*scale, 0.0, 0.0);
    lines->InsertNextCell(2,ptIds);
    colors->InsertNextValue(this->RGB[0]);
    colors->InsertNextValue(this->RGB[1]);
    colors->InsertNextValue(this->RGB[2]);
    ptIds[0] = pts->InsertNextPoint(0.0, -0.5*scale, 0.0);
    ptIds[1] = pts->InsertNextPoint(0.0,  0.5*scale, 0.0);
    lines->InsertNextCell(2,ptIds);
    colors->InsertNextValue(this->RGB[0]);
    colors->InsertNextValue(this->RGB[1]);
    colors->InsertNextValue(this->RGB[2]);
    }
}
