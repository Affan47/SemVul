PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Interpolate: " << (this->Interpolate ? "On\n" : "Off\n");
  os << indent << "Repeat:      " << (this->Repeat ? "On\n" : "Off\n");
  os << indent << "EdgeClamp:   " << (this->EdgeClamp ? "On\n" : "Off\n");
  os << indent << "Quality:     ";
  switch (this->Quality)
    {
    case VTK_TEXTURE_QUALITY_DEFAULT:
      os << "Default\n";
      break;
    case VTK_TEXTURE_QUALITY_16BIT:
      os << "16Bit\n";
      break;
    case VTK_TEXTURE_QUALITY_32BIT:
      os << "32Bit\n";
      break;
    }
  os << indent << "MapColorScalarsThroughLookupTable: " <<
    (this->MapColorScalarsThroughLookupTable  ? "On\n" : "Off\n");
  os << indent << "PremultipliedAlpha: " << (this->PremultipliedAlpha ? "On\n" : "Off\n");

  if ( this->GetInput() )
    {
    os << indent << "Input: (" << static_cast<void *>(this->GetInput()) << ")\n";
    }
  else
    {
    os << indent << "Input: (none)\n";
    }
  if ( this->LookupTable )
    {
    os << indent << "LookupTable:\n";
    this->LookupTable->PrintSelf (os, indent.GetNextIndent ());
    }
  else
    {
    os << indent << "LookupTable: (none)\n";
    }

  if ( this->MappedScalars )
    {
    os << indent << "Mapped Scalars: " << this->MappedScalars << "\n";
    }
  else
    {
    os << indent << "Mapped Scalars: (none)\n";
    }

  if ( this->Transform )
    {
    os << indent << "Transform: " << this->Transform << "\n";
    }
  else
    {
    os << indent << "Transform: (none)\n";
    }
  os << indent << "MultiTexture Blending Mode:     ";
  switch (this->BlendingMode)
    {
    case VTK_TEXTURE_BLENDING_MODE_NONE:
      os << "None\n";
      break;
    case VTK_TEXTURE_BLENDING_MODE_REPLACE:
      os << "Replace\n";
      break;
    case VTK_TEXTURE_BLENDING_MODE_MODULATE:
      os << "Modulate\n";
      break;
    case VTK_TEXTURE_BLENDING_MODE_ADD:
      os << "Add\n";
      break;
    case VTK_TEXTURE_BLENDING_MODE_ADD_SIGNED:
      os << "Add Signed\n";
      break;
    case VTK_TEXTURE_BLENDING_MODE_INTERPOLATE:
      os << "Interpolate\n";
      break;
    case VTK_TEXTURE_BLENDING_MODE_SUBTRACT:
      os << "Subtract\n";
      break;
    }
  os << indent << "RestrictPowerOf2ImageSmaller:   " << (this->RestrictPowerOf2ImageSmaller ? "On\n" : "Off\n");
}
