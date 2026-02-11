GetModelMetadata()
{
  if (!this->ModelMetadata)
    {
    this->ModelMetadata = vtkModelMetadata::New();
    this->ModelMetadata->Register(this);
    }

  return this->ModelMetadata;
}
