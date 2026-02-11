MapScalars(double alpha)
{
  int cellFlag = 0;

  vtkDataArray *scalars = vtkAbstractMapper::
    GetScalars(this->GetInput(), this->ScalarMode, this->ArrayAccessMode,
               this->ArrayId, this->ArrayName, cellFlag);


  if (scalars == 0 || scalars->GetNumberOfComponents() <= this->ArrayComponent)
    {
    this->ArrayComponent = 0;
    }

  if ( !this->ScalarVisibility || scalars==0 || this->GetInput()==0)
    {
    if ( this->ColorCoordinates )
      {
      this->ColorCoordinates->UnRegister(this);
      this->ColorCoordinates = 0;
      }
    if ( this->ColorTextureMap )
      {
      this->ColorTextureMap->UnRegister(this);
      this->ColorTextureMap = 0;
      }
    if ( this->Colors )
      {
      this->Colors->UnRegister(this);
      this->Colors = 0;
      }
    return 0;
    }


  if ( scalars->GetLookupTable() )
    {
    this->SetLookupTable(scalars->GetLookupTable());
    }
  else
    {

    if ( this->LookupTable == 0 )
      {
      this->CreateDefaultLookupTable();
      }
    this->LookupTable->Build();
    }

  if ( !this->UseLookupTableScalarRange )
    {
    this->LookupTable->SetRange(this->ScalarRange);
    }


  if (this->InterpolateScalarsBeforeMapping && ! cellFlag)
    {


    if ( this->ColorMode != VTK_COLOR_MODE_DEFAULT ||
         (vtkUnsignedCharArray::SafeDownCast(scalars)) == 0 )
      {
      this->MapScalarsToTexture(scalars, alpha);
      return 0;
      }
    }


  if ( this->ColorCoordinates )
    {
    this->ColorCoordinates->UnRegister(this);
    this->ColorCoordinates = 0;
    }
  if ( this->ColorTextureMap )
    {
    this->ColorTextureMap->UnRegister(this);
    this->ColorTextureMap = 0;
    }


  if (this->Colors)
    {
    if (this->LookupTable && this->LookupTable->GetAlpha() == alpha)
      {
      if (this->GetMTime() < this->Colors->GetMTime() &&
          this->GetInput()->GetMTime() < this->Colors->GetMTime() &&
          this->LookupTable->GetMTime() < this->Colors->GetMTime())
        {
        return this->Colors;
        }
      }
    }


  if ( this->Colors )
    {
    this->Colors->UnRegister(this);
    this->Colors = 0;
    }


  double orig_alpha = this->LookupTable->GetAlpha();
  this->LookupTable->SetAlpha(alpha);
  this->Colors = this->LookupTable->
    MapScalars(scalars, this->ColorMode, this->ArrayComponent);
  this->LookupTable->SetAlpha(orig_alpha);

  this->Colors->Register(this);
  this->Colors->Delete();

  return this->Colors;
}
