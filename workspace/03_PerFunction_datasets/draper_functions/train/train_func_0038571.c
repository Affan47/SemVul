ToString()
{
  string s;
  if( object != "") s += object+"::";
  s += name;
  if( nPar == -1)
    s += ",[inf. Args]";
  else if( nPar == 1)
    s += ",["+i2s( nPar)+" Arg]";
  else if( nPar > 1)
    s += ",["+i2s( nPar)+" Args]";
  for( SizeT i=0; i<key.size(); ++i)
    s += ","+key[ i];
  return s;
}
