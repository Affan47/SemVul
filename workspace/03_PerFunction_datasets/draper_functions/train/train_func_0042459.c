UpdateDiscreteCursor(double *q)
{


  vtkIdType ptId = this->ImageData->FindPoint(q);

  if ( ptId == -1 )
    {
    return 0;
    }

  double closestPt[3];
  this->ImageData->GetPoint(ptId,closestPt);

  double origin[3];
  this->ImageData->GetOrigin(origin);
  double spacing[3];
  this->ImageData->GetSpacing(spacing);
  int extent[6];
  this->ImageData->GetExtent(extent);

  int iq[3];
  int iqtemp;
  for (int i = 0; i < 3; i++)
    {

    iqtemp = vtkMath::Round((closestPt[i]-origin[i])/spacing[i]);


    iq[i] = (iqtemp < extent[2*i])?extent[2*i]:((iqtemp > extent[2*i+1])?extent[2*i+1]:iqtemp);


    q[i] = iq[i]*spacing[i] + origin[i];

    this->CurrentCursorPosition[i] = iq[i];
    }

  this->CurrentImageValue = this->ImageData->GetScalarComponentAsDouble( \
                   static_cast<int>(this->CurrentCursorPosition[0]),
                   static_cast<int>(this->CurrentCursorPosition[1]),
                   static_cast<int>(this->CurrentCursorPosition[2]),0);
  return 1;
}
