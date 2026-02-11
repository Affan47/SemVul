RequestData(
  vtkInformation *request,
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  this->Superclass::RequestData(request, inputVector, outputVector);

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkImageStencilData *data = vtkImageStencilData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkImplicitFunction *function = this->Input;
  double *spacing = data->GetSpacing();
  double *origin = data->GetOrigin();
  double threshold = this->Threshold;


  if (!function)
    {
    return 1;
    }


  double point[3];


  unsigned long count = 0;
  int extent[6];
  data->GetExtent(extent);
  unsigned long target = static_cast<unsigned long>(
    (extent[5] - extent[4] + 1)*(extent[3] - extent[2] + 1)/50.0);
  target++;


  for (int idZ = extent[4]; idZ <= extent[5]; idZ++)
    {
    point[2] = idZ*spacing[2] + origin[2];

    for (int idY = extent[2]; idY <= extent[3]; idY++)
      {
      point[1] = idY*spacing[1] + origin[1];
      int state = 1;
      int r1 = extent[0];
      int r2 = extent[1];

      if (count%target == 0)
        {
        this->UpdateProgress(count/(50.0*target));
        }
      count++;

      for (int idX = extent[0]; idX <= extent[1]; idX++)
        {
        point[0] = idX*spacing[0] + origin[0];
        int newstate = 1;
        if (function->FunctionValue(point) < threshold)
          {
          newstate = -1;
          if (newstate != state)
            {
            r1 = idX;
            }
          }
        else if (newstate != state)
          {
          r2 = idX - 1;
          data->InsertNextExtent(r1, r2, idY, idZ);
          }
        state = newstate;
        }
      if (state == -1)
        {
        data->InsertNextExtent(r1, extent[1], idY, idZ);
        }
      }
    }

  return 1;
}
