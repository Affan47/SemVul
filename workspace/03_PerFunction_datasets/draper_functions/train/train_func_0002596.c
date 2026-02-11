vtkROIStencilSourceEllipsoid(
  vtkROIStencilSource *self, vtkImageStencilData *data,
  const int extent[6], const double origin[3], const double spacing[3])
{
  int subextent[6];
  double icenter[3];
  double iradius[3];

  vtkROIStencilSourceSubExtent(self, origin, spacing, extent,
    subextent, icenter, iradius);


  unsigned long count = 0;
  unsigned long target = static_cast<unsigned long>(
    (subextent[5] - subextent[4] + 1)*
    (subextent[3] - subextent[2] + 1)/50.0);
  target++;

  for (int idZ = subextent[4]; idZ <= subextent[5]; idZ++)
    {
    double z = (idZ - icenter[2])/iradius[2];

    for (int idY = subextent[2]; idY <= subextent[3]; idY++)
      {
      if (count%target == 0)
        {
        self->UpdateProgress(count/(50.0*target));
        }
      count++;

      double y = (idY - icenter[1])/iradius[1];
      double x2 = 1.0 - y*y - z*z;
      if (x2 < 0)
        {
        continue;
        }
      double x = sqrt(x2);

      int r1 = subextent[0];
      int r2 = subextent[1];
      double xmin = icenter[0] - x*iradius[0];
      double xmax = icenter[0] + x*iradius[0];

      if (r1 < xmin)
        {
        r1 = vtkMath::Floor(xmin) + 1;
        }
      if (r2 > xmax)
        {
        r2 = vtkMath::Floor(xmax);
        }

      if (r2 >= r1)
        {
        data->InsertNextExtent(r1, r2, idY, idZ);
        }
      }
    }

  return 1;
}
