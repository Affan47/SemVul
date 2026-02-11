GetObjectAttributeIndex( int otyp, int oi, const char* attribName )
{
  std::map<int,std::vector<BlockInfoType> >::iterator it = this->BlockInfo.find( otyp );
  if ( it != this->BlockInfo.end() )
    {
    int N = (int) it->second.size();
    if ( oi < 0 || oi >= N )
      {
      vtkDebugMacro( "You requested block " << oi << " in a collection of only " << N << " blocks." );
      return -1;
      }
    oi = this->SortedObjectIndices[otyp][oi];
    N = (int) it->second[oi].AttributeNames.size();
    int ai;
    for ( ai = 0; ai < N; ++ai )
      {
      if ( it->second[oi].AttributeNames[ai] == attribName )
        {
        return ai;
        }
      }
    return -1;
    }
  vtkDebugMacro( "Could not find collection of blocks of type " << otyp <<
    " (" << objtype_names[this->GetObjectTypeIndexFromObjectType(otyp)] << ")." );
  return -1;
}
