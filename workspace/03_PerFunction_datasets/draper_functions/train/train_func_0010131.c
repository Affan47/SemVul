search( const char *path, int offset )
{

  if ( offset == 0 )
  {
    if ( path[0] == '.' )
    {
      if ( path[1] == 0 )
      {
	return this;
      }
      else if ( path[1] == '/' )
      {
	Node *nn = this;
	while ( nn->parent_ ) nn = nn->parent_;
	if ( path[2]==0 )
	{
	  return nn;
	}
	return nn->search( path+2, 2 );
      }
    }
    offset = strlen( path_ ) + 1;
  }

  int len = strlen( path_ );
  if ( len < offset-1 ) return 0;
  len -= offset;
  if ( ( len <= 0 ) || ( strncmp( path, path_+offset, len ) == 0 ) )
  {
    if ( len > 0 && path[ len ] == 0 )
      return this;
    if ( len <= 0 || path[ len ] == '/' )
    {
      for ( Node *nd = child_; nd; nd = nd->next_ )
      {
	Node *nn = nd->search( path, offset );
	if ( nn ) return nn;
      }
      return 0;
    }
  }
  return 0;
}
