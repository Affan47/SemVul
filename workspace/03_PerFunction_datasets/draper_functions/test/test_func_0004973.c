gribCheckSeek(int fileID, long *offset, int *version)
{
  int ierr;
  char buffer[4];

  ierr = gribFileSeek(fileID, offset);

  *version = -1;
  if ( !ierr )
    {
      if ( fileRead(fileID, buffer, 4) == 4 )
	*version = buffer[3];
    }

  return (ierr);
}
