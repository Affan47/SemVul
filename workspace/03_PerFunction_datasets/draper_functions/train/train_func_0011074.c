FindArrayInfoByName( int otyp, const char* name )
{
  std::vector<ArrayInfoType>::iterator ai;
  for ( ai = this->ArrayInfo[otyp].begin(); ai != this->ArrayInfo[otyp].end(); ++ai )
    {
    if ( ai->Name == name )
      return &(*ai);
    }
  return 0;
}
