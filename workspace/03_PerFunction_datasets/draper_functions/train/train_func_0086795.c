WritePData(vtkIndent indent)
{
  this->Superclass::WritePData(indent);
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return;
    }

  vtkRectilinearGrid* input = this->GetInput();
  this->WritePCoordinates(input->GetXCoordinates(), input->GetYCoordinates(),
                          input->GetZCoordinates(), indent);
}
