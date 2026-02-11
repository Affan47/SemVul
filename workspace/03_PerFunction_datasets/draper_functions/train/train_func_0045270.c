PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  if ( this->LineProperty )
    {
    os << indent << "Line Property: " << this->LineProperty << "\n";
    }
  else
    {
    os << indent << "Line Property: (none)\n";
    }
  if ( this->SelectedLineProperty )
    {
    os << indent << "Selected Line Property: "
       << this->SelectedLineProperty << "\n";
    }
  else
    {
    os << indent << "Selected Line Property: (none)\n";
    }

  if ( this->EndPointProperty )
    {
    os << indent << "End Point Property: " << this->EndPointProperty << "\n";
    }
  else
    {
    os << indent << "End Point Property: (none)\n";
    }
  if ( this->SelectedEndPointProperty )
    {
    os << indent << "Selected End Point Property: " << this->SelectedEndPointProperty << "\n";
    }
  else
    {
    os << indent << "Selected End Point Property: (none)\n";
    }

  if ( this->EndPoint2Property )
    {
    os << indent << "End Point Property: " << this->EndPoint2Property << "\n";
    }
  else
    {
    os << indent << "End Point Property: (none)\n";
    }
  if ( this->SelectedEndPoint2Property )
    {
    os << indent << "Selected End Point Property: " << this->SelectedEndPoint2Property << "\n";
    }
  else
    {
    os << indent << "Selected End Point Property: (none)\n";
    }

  os << indent << "Tolerance: " << this->Tolerance << "\n";

  os << indent << "Constrain To Bounds: "
     << (this->ClampToBounds ? "On\n" : "Off\n");

  int res = this->LineSource->GetResolution();
  double *pt1 = this->LineSource->GetPoint1();
  double *pt2 = this->LineSource->GetPoint2();

  os << indent << "Resolution: " << res << "\n";
  os << indent << "Point 1: (" << pt1[0] << ", "
                               << pt1[1] << ", "
                               << pt1[2] << ")\n";
  os << indent << "Point 2: (" << pt2[0] << ", "
                               << pt2[1] << ", "
                               << pt2[2] << ")\n";

  os << indent << "Point1 Representation: ";
  this->Point1Representation->PrintSelf(os,indent.GetNextIndent());

  os << indent << "Point2 Representation: ";
  this->Point2Representation->PrintSelf(os,indent.GetNextIndent());

  os << indent << "Line Handle Representation: ";
  this->LineHandleRepresentation->PrintSelf(os,indent.GetNextIndent());

  os << indent << "Representation State: " << this->RepresentationState << "\n";

  os << indent << "DistanceAnnotationVisibility: ";
  if ( this->DistanceAnnotationVisibility )
    {
    os << this->DistanceAnnotationVisibility << "\n";
    }
  else
    {
    os << "(none)\n";
    }

  os << indent << "DistanceAnnotationFormat: ";
  if ( this->DistanceAnnotationFormat )
    {
    os << this->DistanceAnnotationFormat << "\n";
    }
  else
    {
    os << "(none)\n";
    }

  os << indent << "TextActor: ";
  if ( this->TextActor )
    {
    os << this->TextActor << "\n";
    }
  else
    {
    os << "(none)\n";
    }


}
