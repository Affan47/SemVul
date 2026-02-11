PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  if ( this->ClipFunction )
    {
    os << indent << "Clip Function: " << this->ClipFunction << "\n";
    }
  else
    {
    os << indent << "Clip Function: (none)\n";
    }
  os << indent << "InsideOut: " << (this->InsideOut ? "On\n" : "Off\n");
  os << indent << "Value: " << this->Value << "\n";
  os << indent << "Merge Tolerance: " << this->MergeTolerance << "\n";
  if ( this->Locator )
    {
    os << indent << "Locator: " << this->Locator << "\n";
    }
  else
    {
    os << indent << "Locator: (none)\n";
    }

  os << indent << "Generate Clip Scalars: "
     << (this->GenerateClipScalars ? "On\n" : "Off\n");

  os << indent << "Generate Clipped Output: "
     << (this->GenerateClippedOutput ? "On\n" : "Off\n");

  os << indent << "Mixed 3D Cell Type: "
     << (this->Mixed3DCellGeneration ? "On\n" : "Off\n");
}
