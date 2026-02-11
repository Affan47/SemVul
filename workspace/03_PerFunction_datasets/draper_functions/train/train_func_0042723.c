cdfReadRecord(stream_t *streamptr, double *data, int *nmiss)
{
  int ierr = 0;
  int levelID, varID, tsID, recID, vrecID;

  if ( CDI_Debug ) Message("streamID = %d", streamptr->self);

  tsID    = streamptr->curTsID;
  vrecID  = streamptr->tsteps[tsID].curRecID;
  recID   = streamptr->tsteps[tsID].recIDs[vrecID];
  varID   = streamptr->tsteps[tsID].records[recID].varID;
  levelID = streamptr->tsteps[tsID].records[recID].levelID;

  cdfReadVarSliceDP(streamptr, varID, levelID, data, nmiss);

  return (ierr);
}
