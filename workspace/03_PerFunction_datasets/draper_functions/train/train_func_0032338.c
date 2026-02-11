PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
  os << indent << "LabelSizeArrayName: " << this->LabelSizeArrayName << "\n";
  os << indent << "FontProperties: ";
  std::map<int, vtkSmartPointer<vtkTextProperty> >::iterator it, itEnd;
  it = this->Implementation->FontProperties.begin();
  itEnd = this->Implementation->FontProperties.end();
  for ( ; it != itEnd; ++it )
    {
    os << indent << "  " << it->first << ": " << it->second.GetPointer() << endl;
    }
  os << indent << "FontUtil: " << this->FontUtil << "\n";
}
