GetExtentForPiece(int piece, int* extent)
{
  if((!this->ExtentTable) || (piece < 0) ||
     (piece >= this->NumberOfPiecesInTable))
    {
    vtkErrorMacro("Piece " << piece << " does not exist.  "
                  "NumberOfPiecesInTable is " << this->NumberOfPiecesInTable);
    extent[0] = extent[2] = extent[4] = 0;
    extent[1] = extent[3] = extent[5] = -1;
    return;
    }
  memcpy(extent, this->ExtentTable+piece*6, sizeof(int)*6);
}
