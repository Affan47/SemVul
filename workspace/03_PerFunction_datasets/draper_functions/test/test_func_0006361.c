RequestData(
  vtkInformation *,
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkImageData *inData = vtkImageData::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkImageStencilData *data = vtkImageStencilData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  int extent[6];
  inData->GetExtent(extent);

  this->AllocateOutputData(data, extent);

  vtkDataArray *inScalars = inData->GetPointData()->GetScalars();
  double upperThreshold = this->UpperThreshold;
  double lowerThreshold = this->LowerThreshold;


  unsigned long count = 0;
  unsigned long target = static_cast<unsigned long>(
    (extent[5] - extent[4] + 1)*(extent[3] - extent[2] + 1)/50.0);
  target++;

  for (int idZ = extent[4]; idZ <= extent[5]; idZ++)
    {
    for (int idY = extent[2]; idY <= extent[3]; idY++)
      {
      if (count%target == 0)
        {
        this->UpdateProgress(count/(50.0*target));
        }
      count++;

      int state = 1;
      int r1 = extent[0];
      int r2 = extent[1];


      int idS = ((extent[1] - extent[0] + 1)*
                 ((extent[3] - extent[2] + 1)*(idZ - extent[4]) +
                  (idY - extent[2])));

      for (int idX = extent[0]; idX <= extent[1]; idX++)
        {
        int newstate = 1;
        double value = inScalars->GetComponent(idS++,0);
        if (value >= lowerThreshold && value <= upperThreshold)
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
      if (state < 0)
        {
        data->InsertNextExtent(r1, extent[1], idY, idZ);
        }
      }
    }

  return 1;
}
