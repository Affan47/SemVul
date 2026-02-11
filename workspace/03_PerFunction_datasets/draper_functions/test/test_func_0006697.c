DeepCopy (vtkCellArray *ca)
{

  if (ca == NULL)
    {
    return;
    }

  this->Ia->DeepCopy(ca->Ia);
  this->NumberOfCells = ca->NumberOfCells;
  this->InsertLocation = ca->InsertLocation;
  this->TraversalLocation = ca->TraversalLocation;
}
