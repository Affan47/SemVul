PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "LookupTable: " << this->GetLookupTable() << "\n";
  os << indent << "OutputFormat: " <<
    (this->OutputFormat == VTK_RGBA ? "RGBA" :
     (this->OutputFormat == VTK_RGB ? "RGB" :
      (this->OutputFormat == VTK_LUMINANCE_ALPHA ? "LuminanceAlpha" :
       (this->OutputFormat == VTK_LUMINANCE ? "Luminance" : "Unknown"))))
    << "\n";
  os << indent << "Bypass: " << (this->Bypass ? "On\n" : "Off\n");
}
