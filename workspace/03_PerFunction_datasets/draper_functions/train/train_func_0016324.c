SetLookupTable(vtkLookupTable* lut)
{
  if ( this->LookupTable != lut )
    {
    if ( this->LookupTable )
      {
      this->LookupTable->UnRegister(this);
      }
    this->LookupTable = lut;
    this->LookupTable->Register(this);
    this->Modified();
    }
}
