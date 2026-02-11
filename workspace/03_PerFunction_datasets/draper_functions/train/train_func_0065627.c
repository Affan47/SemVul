pstreamFindID(const char *name)
{
  int pstreamID;
  pstream_t *pstreamptr;

  for ( pstreamID = 0; pstreamID < _pstream_max; pstreamID++ )
    {
      pstreamptr = pstream_to_pointer(pstreamID);

      if ( pstreamptr )
	if ( pstreamptr->name )
	  if ( strcmp(pstreamptr->name, name) == 0 ) break;
    }

  if ( pstreamID == _pstream_max ) pstreamID = -1;

  return (pstreamID);
}
