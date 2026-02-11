cdfDefFC(stream_t *streamptr, int gridID)
{
  char axisname[5] = "nfcX";
  int index, iz = 0;
  int gridID0, gridtype0, gridindex;
  int dimID = UNDEFID;
  int ngrids;
  int fileID;
  int dimlen, dimlen0;
  int vlistID;

  vlistID = streamptr->vlistID;
  fileID  = streamptr->fileID;

  ngrids = vlistNgrids(vlistID);

  dimlen = gridInqSize(gridID)/2;

  for ( index = 0; index < ngrids; index++ )
    {
      if ( streamptr->ydimID[index] != UNDEFID )
        {
          gridID0 = vlistGrid(vlistID, index);
          gridtype0 = gridInqType(gridID0);
          if ( gridtype0 == GRID_FOURIER )
            {
              dimlen0 = gridInqSize(gridID0)/2;
              if ( dimlen == dimlen0 )
                {
                  dimID = streamptr->ydimID[index];
                  break;
                }
              else
                iz++;
            }
        }
    }

  if ( dimID == UNDEFID )
    {
      if ( iz == 0 ) axisname[3] = '\0';
      else           sprintf(&axisname[3], "%1d", iz+1);

      if ( streamptr->ncmode == 2 ) cdf_redef(fileID);

      cdf_def_dim(fileID, axisname, dimlen, &dimID);

      cdf_enddef(fileID);
      streamptr->ncmode = 2;
    }

  gridindex = vlistGridIndex(vlistID, gridID);
  streamptr->ydimID[gridindex] = dimID;
}
