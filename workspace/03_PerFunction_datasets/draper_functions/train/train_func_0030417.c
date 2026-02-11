SetScalarBarActor(vtkScalarBarActor *actor)
{
  vtkScalarBarRepresentation *rep = this->GetScalarBarRepresentation();
  if (!rep)
    {
    this->CreateDefaultRepresentation();
    rep = this->GetScalarBarRepresentation();
    }

  if (rep->GetScalarBarActor() != actor)
    {
    rep->SetScalarBarActor(actor);
    this->Modified();
    }
}
