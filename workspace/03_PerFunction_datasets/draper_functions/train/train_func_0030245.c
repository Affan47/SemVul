PrintSelf(ostream& os, vtkIndent indent)
{

  this->Superclass::PrintSelf(os,indent);

  os << indent << "Display Text: " << (this->DisplayText ? "On\n" : "Off\n");

  os << indent << "Origin: (" << this->Origin[0] << ","
     << this->Origin[1] << "," << this->Origin[2] << ")\n";
  os << indent << "Box Width: " << this->BoxWidth << "\n";
  os << indent << "Circle Width: " << this->CircleWidth << "\n";
  os << indent << "Axes Width: " << this->AxesWidth << "\n";

  if ( this->TextProperty )
    {
    os << indent << "Text Property:\n";
    this->TextProperty->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "Property: (none)\n";
    }

  if ( this->Property )
    {
    os << indent << "Property:\n";
    this->Property->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "Property: (none)\n";
    }

  if ( this->SelectedProperty )
    {
    os << indent << "Selected Property:\n";
    this->SelectedProperty->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "Selected Property: (none)\n";
    }

  if ( this->TextProperty )
    {
    os << indent << "Text Property:\n";
    this->TextProperty->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "Text Property: (none)\n";
    }

}
