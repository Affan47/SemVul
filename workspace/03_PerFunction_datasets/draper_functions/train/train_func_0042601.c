cdfDefGridUUID(stream_t *streamptr, int gridID)
{
  char uuidOfHGrid[17];

  gridInqUUID(gridID, uuidOfHGrid);
  if ( uuidOfHGrid[0] != 0 )
    {
      char uuidOfHGridStr[37];
      uuid2str(uuidOfHGrid, uuidOfHGridStr);
      if ( uuidOfHGridStr[0] != 0 && strlen(uuidOfHGridStr) == 36 )
        {
          int fileID  = streamptr->fileID;

          cdf_put_att_text(fileID, NC_GLOBAL, "uuidOfHGrid", 36, uuidOfHGridStr);

        }
    }
}
