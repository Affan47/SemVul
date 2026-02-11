PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "ContentType: ";
  switch (this->GetContentType())
    {
    case GLOBALIDS:
      os << "GLOBALIDS";
      break;
    case PEDIGREEIDS:
      os << "PEDIGREEIDS";
      break;
    case VALUES:
      os << "VALUES";
      break;
    case INDICES:
      os << "INDICES";
      break;
    case FRUSTUM:
      os << "FRUSTUM";
      break;
    case LOCATIONS:
      os << "LOCATIONS";
      break;
    case THRESHOLDS:
      os << "THRESHOLDS";
      break;
    case BLOCKS:
      os << "BLOCKS";
      break;
    default:
      os << "UNKNOWN";
      break;
    }
  os << endl;
  os << indent << "FieldType: ";
  switch (this->GetFieldType())
    {
    case CELL:
      os << "CELL";
      break;
    case POINT:
      os << "POINT";
      break;
    case FIELD:
      os << "FIELD";
      break;
    case VERTEX:
      os << "VERTEX";
      break;
    case EDGE:
      os << "EDGE";
      break;
    case ROW:
      os << "ROW";
      break;
    default:
      os << "UNKNOWN";
      break;
    }
  os << endl;
  os << indent << "Properties: " << (this->Properties ? "" : "(none)") << endl;
  if (this->Properties)
    {
    this->Properties->PrintSelf(os, indent.GetNextIndent());
    }
  os << indent << "SelectionData: " << (this->SelectionData ? "" : "(none)") << endl;
  if (this->SelectionData)
    {
    this->SelectionData->PrintSelf(os, indent.GetNextIndent());
    }
  os << indent << "QueryString: " << (this->QueryString ? this->QueryString : "NULL") << endl;
}
