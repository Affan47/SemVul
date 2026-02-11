PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Hole: ";
  if (this->Hole)
    {
    os << indent << "On" << "\n";
    }
  else
    {
    os << indent << "Off" << "\n";
    }
  os << indent << "ThickMode: ";
  if (this->ThickMode)
    {
    os << indent << "On" << "\n";
    }
  else
    {
    os << indent << "Off" << "\n";
    }
  os << indent << "HoleWidth: " << this->HoleWidth << endl;
  os << indent << "HoleWidthInPixels: " << this->HoleWidthInPixels << endl;
  os << indent << "Thickness: (" << this->Thickness[0] << ","
     << this->Thickness[1] << "," << this->Thickness[2] << ")" << endl;
  os << indent << "Center: (" << this->Center[0] << "," << this->Center[1]
     << this->Center[2] << endl;
  os << indent << "XAxis: (" << this->XAxis[0] << "," << this->XAxis[1]
     << this->XAxis[2] << endl;
  os << indent << "YAxis: (" << this->YAxis[0] << "," << this->YAxis[1]
     << this->YAxis[2] << endl;
  os << indent << "ZAxis: (" << this->ZAxis[0] << "," << this->ZAxis[1]
     << this->ZAxis[2] << endl;
  os << indent << "Center: (" << this->Center[0] << "," << this->Center[1]
     << this->Center[2] << endl;
  os << indent << "Image: " << this->Image << "\n";
  if (this->Image)
    {
    this->Image->PrintSelf(os, indent);
    }
  os << indent << "PolyData: " << this->PolyData << "\n";
  if (this->PolyData)
    {
    this->PolyData->PrintSelf(os, indent);
    }
  os << indent << "ReslicePlanes: " << this->ReslicePlanes << "\n";
  if (this->ReslicePlanes)
    {
    this->ReslicePlanes->PrintSelf(os, indent);
    }


}
