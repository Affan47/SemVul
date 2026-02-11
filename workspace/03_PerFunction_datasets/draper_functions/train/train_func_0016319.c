Initialize()
{
  if ( this->Points )
    {
    this->Points->UnRegister(this);
    this->Points = NULL;
    }
  this->FreeSearchStructure();
}
