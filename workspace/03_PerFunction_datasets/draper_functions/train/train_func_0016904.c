Initialize()
{
  vtkDataSet::Initialize();

  this->Cleanup();

  if ( this->Locator )
    {
    this->Locator->Initialize();
    }
}
