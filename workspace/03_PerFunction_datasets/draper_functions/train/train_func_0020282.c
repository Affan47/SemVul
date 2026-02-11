GetRGBTransferFunction( int index )
{
  if (this->RGBTransferFunction[index] == NULL )
    {
    this->RGBTransferFunction[index] = vtkColorTransferFunction::New();
    this->RGBTransferFunction[index]->Register(this);
    this->RGBTransferFunction[index]->Delete();
    this->RGBTransferFunction[index]->AddRGBPoint(      0, 0.0, 0.0, 0.0 );
    this->RGBTransferFunction[index]->AddRGBPoint(   1024, 1.0, 1.0, 1.0 );
    if (this->ColorChannels[index] != 3)
      {
      this->ColorChannels[index] = 3;
      }
    this->Modified();
    }

  return this->RGBTransferFunction[index];
}
