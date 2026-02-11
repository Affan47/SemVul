PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  if (this->InputScalarsSelection)
    {
    os << indent << "InputScalarsSelection: "
       << this->InputScalarsSelection << endl;
    }

  os << indent << "Compute Gradients: "
     << (this->ComputeGradients ? "On\n" : "Off\n");
  os << indent << "Compute Normals: "
     << (this->ComputeNormals ? "On\n" : "Off\n");
  os << indent << "Compute Scalars: "
     << (this->ComputeScalars ? "On\n" : "Off\n");

  this->ContourValues->PrintSelf(os,indent.GetNextIndent());

  if ( this->Locator )
    {
    os << indent << "Locator: " << this->Locator << "\n";
    }
  else
    {
    os << indent << "Locator: (none)\n";
    }
}
