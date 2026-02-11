PrintSelf(ostream& os, vtkIndent indent)
{

  this->Superclass::PrintSelf(os,indent);

  if ( this->TextProperty )
    {
    os << indent << "Text Property:\n";
    this->TextProperty->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "Property: (none)\n";
    }

  if ( this->LineProperty )
    {
    os << indent << "Line Property:\n";
    this->LineProperty->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "Line Property: (none)\n";
    }

  if ( this->SelectedLineProperty )
    {
    os << indent << "Selected Line Property:\n";
    this->SelectedLineProperty->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "Selected Line Property: (none)\n";
    }
}
