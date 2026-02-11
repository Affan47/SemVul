PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Limits File Name: "
     << (this->LimitsFileName ? this->LimitsFileName : "(none)") << "\n";
}
