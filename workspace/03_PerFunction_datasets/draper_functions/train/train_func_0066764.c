AllocateOutputData(vtkDataObject *output)
{


  vtkImageData *oImageData = vtkImageData::SafeDownCast(output);
  if (!oImageData)
    {
    return NULL;
    }
  this->AllocateOutputData(oImageData, oImageData->GetExtent());
  return oImageData;
}
