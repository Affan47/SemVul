PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent
     << "Factory DLL path: " << this->LibraryPath << "\n";
  os << indent << "Library version: " << this->LibraryVTKVersion << "\n";
  os << indent << "Compiler used: " << this->LibraryCompilerUsed << "\n";
  os << indent << "Factory description: " << this->GetDescription() << endl;
  int num = this->GetNumberOfOverrides();
  os << indent << "Factory overides " << num << " classes:" << endl;
  indent = indent.GetNextIndent();
  for(int i =0; i < num; i++)
  {
    os << indent << "Class : " <<  this->GetClassOverrideName(i) << endl;
    os << indent << "Overriden with: " <<  this->GetClassOverrideWithName(i)
       << endl;
    os << indent << "Enable flag: " <<  this->GetEnableFlag(i) << endl;
    os << endl;
  }
}
