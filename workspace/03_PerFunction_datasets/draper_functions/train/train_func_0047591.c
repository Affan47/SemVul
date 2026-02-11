PrintSelf(ostream& os, vtkIndent indent)
{

  this->Superclass::PrintSelf(os,indent);

  os << indent << "Distance: " << this->GetDistance() <<"\n";
  os << indent << "Tolerance: " << this->Tolerance <<"\n";
  os << indent << "Handle Representation: " << this->HandleRepresentation << "\n";

  os << indent << "Label Format: ";
  if ( this->LabelFormat )
    {
    os << this->LabelFormat << "\n";
    }
  else
    {
    os << "(none)\n";
    }

  os << indent << "Ruler Mode: "
     << (this->RulerMode ? "On" : "Off") <<"\n";
  os << indent << "Ruler Distance: " << this->GetRulerDistance() <<"\n";
  os << indent << "Number of Ruler Ticks: " << this->GetNumberOfRulerTicks() <<"\n";

  os << indent << "Point1 Representation: ";
  if ( this->Point1Representation )
    {
    this->Point1Representation->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << "(none)\n";
    }

  os << indent << "Point2 Representation: ";
  if ( this->Point2Representation )
    {
    this->Point2Representation->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << "(none)\n";
    }


}
