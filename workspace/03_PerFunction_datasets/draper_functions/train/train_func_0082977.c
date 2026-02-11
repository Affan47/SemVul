ReadPiece(vtkXMLDataElement* ePiece)
{
  if(!this->Superclass::ReadPiece(ePiece))
    {
    return 0;
    }

  if(!ePiece->GetScalarAttribute("NumberOfPoints",
                                 this->NumberOfPoints[this->Piece]))
    {
    vtkErrorMacro("Piece " << this->Piece
                  << " is missing its NumberOfPoints attribute.");
    this->NumberOfPoints[this->Piece] = 0;
    return 0;
    }


  int i;
  this->PointElements[this->Piece] = 0;
  for(i=0; i < ePiece->GetNumberOfNestedElements(); ++i)
    {
    vtkXMLDataElement* eNested = ePiece->GetNestedElement(i);
    if(strcmp(eNested->GetName(), "Points") == 0)
      {

      if( (this->NumberOfTimeSteps > 0 && eNested->GetNumberOfNestedElements() >= 1) ||
          (this->NumberOfTimeSteps == 0 && eNested->GetNumberOfNestedElements() == 1))
        {
        this->PointElements[this->Piece] = eNested;
        }
      }
    }


  if(!this->PointElements[this->Piece] &&
     (this->NumberOfPoints[this->Piece] > 0))
    {
    vtkErrorMacro("A piece is missing its Points element "
                  "or element does not have exactly 1 array.");
    return 0;
    }

  return 1;
}
