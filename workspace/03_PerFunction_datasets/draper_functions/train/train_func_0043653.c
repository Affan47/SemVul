PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  if ( this->NormalProperty )
    {
    os << indent << "Normal Property: " << this->NormalProperty << "\n";
    }
  else
    {
    os << indent << "Normal Property: (none)\n";
    }
  if ( this->SelectedNormalProperty )
    {
    os << indent << "Selected Normal Property: "
       << this->SelectedNormalProperty << "\n";
    }
  else
    {
    os << indent << "Selected Normal Property: (none)\n";
    }

  if ( this->PlaneProperty )
    {
    os << indent << "Plane Property: " << this->PlaneProperty << "\n";
    }
  else
    {
    os << indent << "Plane Property: (none)\n";
    }
  if ( this->SelectedPlaneProperty )
    {
    os << indent << "Selected Plane Property: "
       << this->SelectedPlaneProperty << "\n";
    }
  else
    {
    os << indent << "Selected Plane Property: (none)\n";
    }

  if ( this->OutlineProperty )
    {
    os << indent << "Outline Property: " << this->OutlineProperty << "\n";
    }
  else
    {
    os << indent << "Outline Property: (none)\n";
    }
  if ( this->SelectedOutlineProperty )
    {
    os << indent << "Selected Outline Property: "
       << this->SelectedOutlineProperty << "\n";
    }
  else
    {
    os << indent << "Selected Outline Property: (none)\n";
    }

  if ( this->EdgesProperty )
    {
    os << indent << "Edges Property: " << this->EdgesProperty << "\n";
    }
  else
    {
    os << indent << "Edges Property: (none)\n";
    }

  os << indent << "Normal To X Axis: "
     << (this->NormalToXAxis ? "On" : "Off") << "\n";
  os << indent << "Normal To Y Axis: "
     << (this->NormalToYAxis ? "On" : "Off") << "\n";
  os << indent << "Normal To Z Axis: "
     << (this->NormalToZAxis ? "On" : "Off") << "\n";

  os << indent << "Tubing: " << (this->Tubing ? "On" : "Off") << "\n";
  os << indent << "Origin Translation: "
     << (this->OriginTranslation ? "On" : "Off") << "\n";
  os << indent << "Outline Translation: "
     << (this->OutlineTranslation ? "On" : "Off") << "\n";
  os << indent << "Outside Bounds: "
     << (this->OutsideBounds ? "On" : "Off") << "\n";
  os << indent << "Scale Enabled: "
     << (this->ScaleEnabled ? "On" : "Off") << "\n";
  os << indent << "Draw Plane: " << (this->DrawPlane ? "On" : "Off") << "\n";

  os << indent << "Diagonal Ratio: " << this->DiagonalRatio << "\n";
}
