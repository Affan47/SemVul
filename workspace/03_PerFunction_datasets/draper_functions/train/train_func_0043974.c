Initialize()
{
  if ( this->PieceActors )
    {
    for (int i=0; i<this->N; i++)
      {
      this->PieceMappers[i]->Delete();
      this->PieceActors[i]->Delete();
      }
    delete [] this->PieceMappers;
    this->PieceMappers = NULL;
    delete [] this->PieceActors;
    this->PieceActors = NULL;
    }

  this->N = 0;
  this->Total = 0.0;
  if ( this->Fractions )
    {
    delete [] this->Fractions;
    }
}
