ConstructFromString(const char *path)
{
  Path.clear();
  if(!path) return false;
  unsigned int flip = 0;
  size_t pos = 0;
  const size_t len = strlen(path);
  if(!len) return false;

  if( path[pos] == '/' )
    {
    ++pos;
    }
  else
    {
    return false;
    }
  while( pos != len )
    {
    Tag t;
    if( flip % 2 == 0 )
      {
      if( t.ReadFromCommaSeparatedString( path+pos ) )
        {
        pos += 4 + 4 + 1;
        Path.push_back( t );
        }
      else
        {
        return false;
        }
      }
    else
      {
      unsigned int value = 0;
      if( path[pos] == '*' )
        {
        t.SetElementTag( 0 );
        pos++;
        Path.push_back( t );
        }
      else if( sscanf(path+pos, "%d/", &value) == 1 )
        {
        }
      }
    ++flip;
    if( pos != len && path[pos] == '/' ) ++pos;

    }
  return true;
}
