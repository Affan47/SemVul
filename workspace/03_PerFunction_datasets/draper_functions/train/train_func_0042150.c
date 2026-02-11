Initialize()
{
  if ( this->BarActors )
    {
    for (int i=0; i<this->N; i++)
      {
      this->BarMappers[i]->Delete();
      this->BarActors[i]->Delete();
      }
    delete [] this->BarMappers;
    this->BarMappers = NULL;
    delete [] this->BarActors;
    this->BarActors = NULL;
    }

  this->N = 0;
  if ( this->Heights )
    {
    delete [] this->Heights;
    this->Heights = NULL;
    }
}
