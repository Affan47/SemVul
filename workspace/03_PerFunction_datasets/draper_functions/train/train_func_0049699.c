WriteInlineMode(vtkIndent indent)
{
  ostream& os = *(this->Stream);
  vtkIndent nextIndent = indent.GetNextIndent();


  os << nextIndent << "<Piece";
  this->WriteInlinePieceAttributes();
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return 0;
    }
  os << ">\n";

  this->WriteInlinePiece(nextIndent.GetNextIndent());
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return 0;
    }


  os << nextIndent << "</Piece>\n";

  return 1;
}
