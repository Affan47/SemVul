cdfDefVarMissval(stream_t *streamptr, int varID, int dtype, int lcheck)
{
  if ( streamptr->vars[varID].defmiss == FALSE )
    {
      int fileID;
      int ncvarid;
      double missval;
      int vlistID;
      int xtype;

      vlistID = streamptr->vlistID;
      fileID  = streamptr->fileID;
      ncvarid = streamptr->vars[varID].ncvarid;
      missval = vlistInqVarMissval(vlistID, varID);

      if ( lcheck && streamptr->ncmode == 2 ) cdf_redef(fileID);

      xtype = cdfDefDatatype(dtype, streamptr->filetype);

      if ( xtype == NC_BYTE && missval > 127 && missval < 256 ) xtype = NC_INT;

      cdf_put_att_double(fileID, ncvarid, "_FillValue", (nc_type) xtype, 1, &missval);
      cdf_put_att_double(fileID, ncvarid, "missing_value", (nc_type) xtype, 1, &missval);

      if ( lcheck && streamptr->ncmode == 2 ) cdf_enddef(fileID);

      streamptr->vars[varID].defmiss = TRUE;
    }
}
