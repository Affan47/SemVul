BuildAdjacency( vtkDataSet *inData )
{
  vtkImageData *image = vtkImageData::SafeDownCast(inData);

  int ncells = image->GetNumberOfCells();


  vtkIdList *ptIds = vtkIdList::New();
  vtkIdType uId[6] = {0,1,2,3,0,1};
  vtkIdType vId[6] = {1,2,3,0,2,3};
  double cost;

  for ( int i = 0; i < ncells; ++i )
    {
    image->GetCellPoints ( i, ptIds );

    for( int j = 0; j < 6; ++j )
      {
      vtkIdType u = ptIds->GetId( vId[j] );
      vtkIdType v = ptIds->GetId( uId[j] );


      std::map<int,double>& mu = this->Internals->Adjacency[u];
      if ( mu.find(v) == mu.end() )
        {
        cost = this->CalculateStaticEdgeCost( image, u, v );
        mu.insert( std::pair<int,double>( v, cost ) );
        }

      std::map<int,double>& mv = this->Internals->Adjacency[v];
      if ( mv.find(u) == mv.end() )
        {
        cost = this->CalculateStaticEdgeCost( image, v, u );
        mv.insert( std::pair<int,double>( u, cost ) );
        }
      }
    }

  ptIds->Delete();

  this->RebuildStaticCosts = false;
  this->AdjacencyBuildTime.Modified();
}
