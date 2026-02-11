PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Output Field: ";
  if ( this->OutputField == VTK_DATA_OBJECT_FIELD )
    {
    os << "DataObjectField\n";
    }
  else if ( this->OutputField == VTK_POINT_DATA_FIELD )
    {
    os << "PointDataField\n";
    }
  else
    {
    os << "CellDataField\n";
    }

}
