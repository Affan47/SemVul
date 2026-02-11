PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  if (this->MedicalImageProperties)
    {
    os << indent << "Medical Image Properties:\n";
    this->MedicalImageProperties->PrintSelf(os, indent.GetNextIndent());
    }
  else
    {
    os << indent << "MedicalImageProperties: (none)\n";
    }
}
