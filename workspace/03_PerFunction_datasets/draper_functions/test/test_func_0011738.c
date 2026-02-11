PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Output Style: ";
  if ( this->OutputStyle == VTK_STYLE_PIXELIZE )
    {
    os << indent << "Pixelize\n";
    }
  else if ( this->OutputStyle == VTK_STYLE_RUN_LENGTH )
    {
    os << indent << "RunLength\n";
    }
  else
    {
    os << indent << "Polygonalize\n";
    }

  os << indent << "Color Mode: ";
  if ( this->ColorMode == VTK_STYLE_PIXELIZE )
    {
    os << indent << "LUT\n";
    }
  else
    {
    os << indent << "Linear256\n";
    }

  os << indent << "Smoothing: " << (this->Smoothing ? "On\n" : "Off\n");
  os << indent << "Number of Smoothing Iterations: "
     << this->NumberOfSmoothingIterations << "\n";

  os << indent << "Decimation: " << (this->Decimation ? "On\n" : "Off\n");
  os << indent << "Decimation Error: "
     << (this->DecimationError ? "On\n" : "Off\n");

  os << indent << "Error: " << this->Error << "\n";
  os << indent << "Sub-Image Size: " << this->SubImageSize << "\n";

  if ( this->LookupTable )
    {
    os << indent << "LookupTable:\n";
    this->LookupTable->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "LookupTable: (none)\n";
    }

}
