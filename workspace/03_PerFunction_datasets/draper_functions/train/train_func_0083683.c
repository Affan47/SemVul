WriteAppendedPiece(int index,
                                                     vtkIndent indent)
{
  this->Superclass::WriteAppendedPiece(index, indent);
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return;
    }

  this->WriteCoordinatesAppended(this->GetInput()->GetXCoordinates(),
                                 this->GetInput()->GetYCoordinates(),
                                 this->GetInput()->GetZCoordinates(),
                                 indent, &this->CoordinateOM->GetPiece(index));
}
