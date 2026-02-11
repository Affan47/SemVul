PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  if ( this->CutFunction )
    {
    os << indent << "Cut Function: " << this->CutFunction << "\n";
    }
  else
    {
    os << indent << "Cut Function: (none)\n";
    }

  os << indent << "Sort By: " << this->GetSortByAsString() << "\n";

  if ( this->Locator )
    {
    os << indent << "Locator: " << this->Locator << "\n";
    }
  else
    {
    os << indent << "Locator: (none)\n";
    }

  this->ContourValues->PrintSelf(os,indent.GetNextIndent());

  os << indent << "Generate Cut Scalars: "
     << (this->GenerateCutScalars ? "On\n" : "Off\n");
}
