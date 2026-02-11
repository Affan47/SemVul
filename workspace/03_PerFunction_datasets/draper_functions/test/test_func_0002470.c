spacegroup_number() const
{
  for ( int i = 0; i < data::sgdata_size; i++ )
    if ( data::sgdata[i].sghash == hash_ ) return data::sgdata[i].num;
  return 0;
}
