gribCheckFiletype(int fileID)
{
  int ierr;
  int found = 0;
  char buffer[4];

  if ( fileRead(fileID, buffer, 4) != 4 ) return(found);

  if ( memcmp(buffer, "GRIB", 4) == 0 )
    {
      found = 1;
      if ( CGRIBEX_Debug ) Message("found GRIB file = %s", fileInqName(fileID));
    }
  else
    {
      long offset;

      ierr = gribFileSeek(fileID, &offset);
      fileRewind(fileID);
      if ( !ierr )
	{
	  found = 1;
	  if ( CGRIBEX_Debug ) Message("found seek GRIB file = %s", fileInqName(fileID));
	}
    }

  return (found);
}
