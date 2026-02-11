PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "FileName: "
     << (this->FileName ? this->FileName : "(NULL)") << endl;
  os << indent << "ReplaceFillValueWithNan: "
     << this->ReplaceFillValueWithNan << endl;

  os << indent << "VariableArraySelection:" << endl;
  this->VariableArraySelection->PrintSelf(os, indent.GetNextIndent());
  os << indent << "AllVariableArrayNames:" << endl;
  this->GetAllVariableArrayNames()->PrintSelf(os, indent.GetNextIndent());
  os << indent << "VariableDimensions: " << this->VariableDimensions << endl;
  os << indent << "AllDimensions: " << this->AllDimensions << endl;
}
