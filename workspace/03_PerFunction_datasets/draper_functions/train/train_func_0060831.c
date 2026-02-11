PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "XYZ File Name: " <<
    (this->XYZFileName ? this->XYZFileName : "(none)") << "\n";
  os << indent << "Q File Name: " <<
    (this->QFileName ? this->QFileName : "(none)") << "\n";
  os << indent << "Function File Name: " <<
    (this->FunctionFileName ? this->FunctionFileName : "(none)") << "\n";
  os << indent << "BinaryFile: " << this->BinaryFile << endl;
  os << indent << "HasByteCount: " << this->HasByteCount << endl;
  os << indent << "Gamma: " << this->Gamma << endl;
  os << indent << "R: " << this->R << endl;
  os << indent << "Uvinf: " << this->Uvinf << endl;
  os << indent << "Vvinf: " << this->Vvinf << endl;
  os << indent << "Wvinf: " << this->Wvinf << endl;
  os << indent << "ScalarFunctionNumber: " << this->ScalarFunctionNumber << endl;
  os << indent << "VectorFunctionNumber: " << this->VectorFunctionNumber << endl;
  os << indent << "MultiGrid: " << this->MultiGrid << endl;
  os << indent << "TwoDimensionalGeometry: "
     << this->TwoDimensionalGeometry << endl;
  os << indent << "DoNotReduceNumberOfOutputs: "
     << this->DoNotReduceNumberOfOutputs << endl;
  os << indent << "ForceRead: " << this->ForceRead << endl;
  os << indent << "IBlanking: " << this->IBlanking << endl;
  os << indent << "ByteOrder: " << this->ByteOrder << endl;
  os << indent << "TwoDimensionalGeometry: " << (this->TwoDimensionalGeometry?"on":"off")
     << endl;
}
