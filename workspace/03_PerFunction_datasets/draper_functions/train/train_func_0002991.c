PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "FileName: "
     << (this->FileName? this->FileName:"") << "\n";
  os << indent << "FileDataType: "
     << (this->FileDataType? this->FileDataType:"") << "\n";
  os << indent << "FileVersion: "
     << (this->FileVersion? this->FileVersion:"") << "\n";
}
