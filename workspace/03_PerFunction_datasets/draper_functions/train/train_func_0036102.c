GetExecutive()
{

  if(!this->HasExecutive())
    {
    vtkExecutive* e = this->CreateDefaultExecutive();
    this->SetExecutive(e);
    e->Delete();
    }
  return this->Executive;
}
