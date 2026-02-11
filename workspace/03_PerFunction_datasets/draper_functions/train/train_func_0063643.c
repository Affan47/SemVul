PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  const char* name = this->GetName();
  if (name)
    {
    os << indent << "Name: " << name << "\n";
    }
  else
    {
    os << indent << "Name: (none)\n";
    }
  os << indent << "Data type: " << this->GetDataTypeAsString() << "\n";
  os << indent << "Size: " << this->Size << "\n";
  os << indent << "MaxId: " << this->MaxId << "\n";
  os << indent << "NumberOfComponents: " << this->NumberOfComponents << endl;
  if ( this->ComponentNames )
    {
    os << indent << "ComponentNames: " << endl;
    vtkIndent nextIndent = indent.GetNextIndent();
    for ( unsigned int i=0; i < this->ComponentNames->size(); ++i )
      {
      os << nextIndent << i << " : " << this->ComponentNames->at(i) << endl;
      }
    }
  os << indent << "Information: " << this->Information << endl;
  if ( this->Information )
    {
    this->Information->PrintSelf( os, indent.GetNextIndent() );
    }
}
