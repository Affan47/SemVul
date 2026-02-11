PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Error Measure: ";
  if ( this->ErrorMeasure == VTK_ERROR_NUMBER_OF_TRIANGLES )
    {
    os << "Number of triangles\n";
    os << indent << "Number of triangles: " << this->NumberOfTriangles << "\n";
    }
  else if ( this->ErrorMeasure == VTK_ERROR_SPECIFIED_REDUCTION )
    {
    os << "Specified reduction\n";
    os << indent << "Reduction: " << this->Reduction << "\n";
    }
  else if ( this->ErrorMeasure == VTK_ERROR_ABSOLUTE )
    {
    os << "Absolute\n";
    os << indent << "Absolute Error: " << this->AbsoluteError << "\n";
    }
  else
    {
    os << "Relative\n";
    os << indent << "Relative Error: " << this->RelativeError << "\n";
    }

  os << indent << "BoundaryVertexDeletion: "
     << (this->BoundaryVertexDeletion ? "On\n" : "Off\n");
  os << indent << "ComputeNormals: "
     << (this->ComputeNormals ? "On\n" : "Off\n");
}
