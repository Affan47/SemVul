PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "ImageAttributes: " << this->ImageAttributes << "\n";
  if (this->ImageAttributes)
    {
    this->ImageAttributes->PrintSelf(os, indent.GetNextIndent());
    }
  os << indent << "DirectionCosines: " << this->DirectionCosines << "\n";
  if (this->DirectionCosines)
    {
    this->DirectionCosines->PrintSelf(os, indent.GetNextIndent());
    }
  os << indent << "RescaleSlope: " << this->RescaleSlope << "\n";
  os << indent << "RescaleIntercept: " << this->RescaleIntercept << "\n";
  os << indent << "RescaleRealValues: "
     << (this->RescaleRealValues ? "On" : "Off") << "\n";
  os << indent << "DataRange: (" << this->DataRange[0]
     << ", " << this->DataRange[1] << ")\n";

  os << indent << "NumberOfTimeSteps: " << this->NumberOfTimeSteps << "\n";
  os << indent << "TimeStep: " << this->TimeStep << "\n";
}
