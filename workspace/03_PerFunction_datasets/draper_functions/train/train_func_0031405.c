PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "Opacity: " << this->Opacity << "\n";
  os << indent << "Color: (" << this->Color[0] << ", "
     << this->Color[1] << ", "
     << this->Color[2] << ")\n";
  os << indent << "Point size: " << this->PointSize << "\n";
  os << indent << "Line width: " << this->LineWidth << "\n";
  os << indent << "Line stipple pattern: " << this->LineStipplePattern << "\n";
  os << indent << "Line stipple repeat factor: " << this->LineStippleRepeatFactor << "\n";
  switch ( this->DisplayLocation )
    {
    case VTK_FOREGROUND_LOCATION:
      os << indent << "Display location: foreground\n";
      break;
    case VTK_BACKGROUND_LOCATION:
      os << indent << "Display location: background\n";
      break;
    default:
      os << indent << "Display location: invalid\n";
      break;
    }

}
