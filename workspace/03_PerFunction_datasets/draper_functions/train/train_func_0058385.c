PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "NumberOfThreads: " << this->NumberOfThreads << "\n";

  if ( this->Bypass )
    {
    os << indent << "Bypass: On\n";
    }
  else
    {
    os << indent << "Bypass: Off\n";
    }
}
