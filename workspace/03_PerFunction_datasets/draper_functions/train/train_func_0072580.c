PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  if (this->MeshFileName)
    {
    os << indent << "MeshFileName: " << this->MeshFileName << endl;
    }
  else
    {
    os << indent << "MeshFileName: (null)\n";
    }

  for (unsigned int i = 0; i < this->Internal->ModeFileNames.size(); i++)
    {
    os << indent << "ModeFileName[" << i << "]: "
       << this->Internal->ModeFileNames[i] << endl;
    }

  os << indent << "ReadInternalVolume: " << this->ReadInternalVolume << endl;
  os << indent << "ReadExternalSurface: " << this->ReadExternalSurface << endl;
  os << indent << "ReadMidpoints: " << this->ReadMidpoints << endl;

  os << indent << "VariableArraySelection:" << endl;
  this->Internal->VariableArraySelection->PrintSelf(os, indent.GetNextIndent());
}
