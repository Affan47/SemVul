iegInqContents(stream_t *streamptr)
{
  int fileID;
  int status = 0;

  fileID = streamptr->fileID;

  streamptr->curTsID = 0;

  iegScanTimestep1(streamptr);

  if ( streamptr->ntsteps == -1 ) status = iegScanTimestep2(streamptr);

  fileSetPos(fileID, 0, SEEK_SET);

  return (status);
}
