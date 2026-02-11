DeleteTable()
{
  if(this->TextureUnits!=0)
    {
    size_t i=0;
    size_t c=this->NumberOfTextureUnits;
    bool valid=true;
    while(valid && i<c)
      {
      valid=!this->TextureUnits[i];
      ++i;
      }
    if(!valid)
      {
      vtkErrorMacro(<<"the texture unit is deleted but not some texture unit has not been released: Id="<<i);
      }
    delete[] this->TextureUnits;
    this->TextureUnits=0;
    this->NumberOfTextureUnits=0;
    }
}
