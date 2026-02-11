WriteHeader()
{
  vtkIndent indent = vtkIndent().GetNextIndent();

  ostream& os = *(this->Stream);

  if(!this->WritePrimaryElement(os, indent))
    {
    return 0;
    }

  this->WriteFieldData(indent.GetNextIndent());

  if(this->DataMode == vtkXMLWriter::Appended)
    {
    vtkIndent nextIndent = indent.GetNextIndent();

    this->AllocatePositionArrays();

    if((this->WritePiece < 0) || (this->WritePiece >= this->NumberOfPieces))
      {

      int i;
      for(i=0; i < this->NumberOfPieces; ++i)
        {

        os << nextIndent << "<Piece";
        this->WriteAppendedPieceAttributes(i);
        if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
          {
          this->DeletePositionArrays();
          return 0;
          }
        os << ">\n";

        this->WriteAppendedPiece(i, nextIndent.GetNextIndent());
        if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
          {
          this->DeletePositionArrays();
          return 0;
          }


        os << nextIndent << "</Piece>\n";
        }
      }
    else
      {


      os << nextIndent << "<Piece";
      this->WriteAppendedPieceAttributes(this->WritePiece);
      if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
        {
        this->DeletePositionArrays();
        return 0;
        }
      os << ">\n";

      this->WriteAppendedPiece(this->WritePiece, nextIndent.GetNextIndent());
      if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
        {
        this->DeletePositionArrays();
        return 0;
        }


      os << nextIndent << "</Piece>\n";
      }


    os << indent << "</" << this->GetDataSetName() << ">\n";
    os.flush();
    if (os.fail())
      {
      this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
      this->DeletePositionArrays();
      return 0;
      }

    this->StartAppendedData();
    if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
      {
      this->DeletePositionArrays();
      return 0;
      }

    }

  return 1;
}
