PrintSelf(
                    ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  os << indent << "ResliceCursor: " << this->ResliceCursor << "\n";
  if (this->ResliceCursor)
    {
    this->ResliceCursor->PrintSelf(os, indent);
    }
  os << indent << "Cutter: " << this->Cutter << "\n";
  if (this->Cutter)
    {
    this->Cutter->PrintSelf(os, indent);
    }
  os << indent << "ExtrusionFilter1: " << this->ExtrusionFilter1 << "\n";
  if (this->ExtrusionFilter1)
    {
    this->ExtrusionFilter1->PrintSelf(os, indent);
    }
  os << indent << "ExtrusionFilter2: " << this->ExtrusionFilter2 << "\n";
  if (this->ExtrusionFilter2)
    {
    this->ExtrusionFilter2->PrintSelf(os, indent);
    }
  os << indent << "ReslicePlaneNormal: " << this->ReslicePlaneNormal << endl;
  os << indent << "Extrude: " << this->Extrude << endl;


}
