CreateDefaultLocator()
{
  if ( this->Locator == NULL )
    {
    this->Locator = vtkPointLocator::New();
    vtkPointLocator::SafeDownCast( this->Locator )->SetDivisions(25,25,25);
    }
}
