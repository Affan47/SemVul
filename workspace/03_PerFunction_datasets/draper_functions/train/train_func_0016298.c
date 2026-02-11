CalculatePieceFractions(float* fractions)
{
  int i;
  int extent[6];


  fractions[0] = 0;
  for(i=0;i < this->NumberOfPieces;++i)
    {

    this->ExtentTranslator->SetPiece(i);
    this->ExtentTranslator->PieceToExtent();
    this->ExtentTranslator->GetExtent(extent);


    fractions[i+1] = fractions[i] + ((extent[1]-extent[0]+1)*
                                     (extent[3]-extent[2]+1)*
                                     (extent[5]-extent[4]+1));
    }
  if(fractions[this->NumberOfPieces] == 0)
    {
    fractions[this->NumberOfPieces] = 1;
    }
  for(i=0;i < this->NumberOfPieces;++i)
    {
    fractions[i+1] = fractions[i+1] / fractions[this->NumberOfPieces];
    }
}
