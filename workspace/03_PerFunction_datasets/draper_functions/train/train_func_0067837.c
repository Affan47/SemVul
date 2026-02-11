PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Projection Normal: ";
  if ( this->ProjectionNormal == vtkBoundedPlanePointPlacer::XAxis )
    {
    os << "XAxis\n";
    }
  else if ( this->ProjectionNormal == vtkBoundedPlanePointPlacer::YAxis )
    {
    os << "YAxis\n";
    }
  else if ( this->ProjectionNormal == vtkBoundedPlanePointPlacer::ZAxis )
    {
    os << "ZAxis\n";
    }
  else
    {
    os << "Oblique\n";
    }

  os << indent << "Projection Position: " << this->ProjectionPosition << "\n";

  os << indent << "Bounding Planes:\n";
  if ( this->BoundingPlanes )
    {
    this->BoundingPlanes->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << " (none)\n";
    }
  os << indent << "Oblique plane:\n";
  if ( this->ObliquePlane )
    {
    this->ObliquePlane->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << " (none)\n";
    }
}
