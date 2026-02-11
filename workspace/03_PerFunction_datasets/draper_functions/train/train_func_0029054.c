InsertLine(
  const double pt1[2], const double pt2[2],
  bool inflection1, bool inflection2)
{
  double x1 = pt1[0];
  double x2 = pt2[0];
  double y1 = pt1[1];
  double y2 = pt2[1];


  if (y1 > y2)
    {
    x1 = pt2[0];
    x2 = pt1[0];
    y1 = pt2[1];
    y2 = pt1[1];
    bool tmp = inflection1;
    inflection1 = inflection2;
    inflection2 = tmp;
    }


  double xmin = x1;
  double xmax = x2;
  if (x1 > x2)
    {
    xmin = x2;
    xmax = x1;
    }


  if (y1 == y2)
    {
    return;
    }

  double ymin = y1;
  double ymax = y2;


  ymin -= inflection1*this->Tolerance;
  ymax += inflection2*this->Tolerance;


  int iy1, iy2;
  iy1 = this->Extent[0];
  iy2 = this->Extent[1];


  if (ymax < iy1 || ymin >= iy2)
    {
    return;
    }


  if (ymin >= iy1)
    {
    iy1 = vtkMath::Floor(ymin) + 1;
    }
  if (ymax < iy2)
    {
    iy2 = vtkMath::Floor(ymax);
    }


  if (iy1 < this->UsedExtent[0] ||
      iy2 > this->UsedExtent[1])
    {
    this->PrepareExtent(iy1, iy2);
    }


  double grad = (x2 - x1)/(y2 - y1);
  double delta = (iy1 - y1)*grad;


  for (int y = iy1; y <= iy2; y++)
    {
    double x = x1 + delta;


    delta += grad;


    x = ((x < xmax) ? x : xmax);
    x = ((x > xmin) ? x : xmin);

    this->InsertPoint(y, x);
    }
}
