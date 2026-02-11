streamDefaultValue ( stream_t * streamptr )
{
  int i;

  streamptr->self              = UNDEFID;
  streamptr->accesstype        = UNDEFID;
  streamptr->accessmode        = 0;
  streamptr->filetype          = UNDEFID;
  streamptr->byteorder         = UNDEFID;
  streamptr->fileID            = 0;
  streamptr->dimgroupID        = UNDEFID;
  streamptr->filemode          = 0;
  streamptr->numvals           = 0;
  streamptr->filename          = NULL;
  streamptr->record            = NULL;
  streamptr->varsAllocated     = 0;
  streamptr->nrecs             = 0;
  streamptr->nvars             = 0;
  streamptr->vars              = NULL;
  streamptr->varinit           = 0;
  streamptr->ncmode            = 0;
  streamptr->curTsID           = UNDEFID;
  streamptr->rtsteps           = 0;
  streamptr->ntsteps           = UNDEFID;
  streamptr->numTimestep       = 0;
  streamptr->tsteps            = NULL;
  streamptr->tstepsTableSize   = 0;
  streamptr->tstepsNextID      = 0;
  streamptr->historyID         = UNDEFID;
  streamptr->vlistID           = UNDEFID;
  streamptr->globalatts        = 0;
  streamptr->localatts         = 0;
  streamptr->vct.ilev          = 0;
  streamptr->vct.mlev          = 0;
  streamptr->vct.ilevID        = UNDEFID;
  streamptr->vct.mlevID        = UNDEFID;
  streamptr->unreduced         = cdiDataUnreduced;
  streamptr->sortname          = cdiSortName;
  streamptr->have_missval      = cdiHaveMissval;
  streamptr->comptype          = COMPRESS_NONE;
  streamptr->complevel         = 0;

  basetimeInit(&streamptr->basetime);

  for ( i = 0; i < MAX_GRIDS_PS; i++ ) streamptr->xdimID[i]   = UNDEFID;
  for ( i = 0; i < MAX_GRIDS_PS; i++ ) streamptr->ydimID[i]   = UNDEFID;
  for ( i = 0; i < MAX_ZAXES_PS; i++ ) streamptr->zaxisID[i]  = UNDEFID;
  for ( i = 0; i < MAX_GRIDS_PS; i++ ) streamptr->ncxvarID[i] = UNDEFID;
  for ( i = 0; i < MAX_GRIDS_PS; i++ ) streamptr->ncyvarID[i] = UNDEFID;
  for ( i = 0; i < MAX_GRIDS_PS; i++ ) streamptr->ncavarID[i] = UNDEFID;

  streamptr->curfile           = 0;
  streamptr->nfiles            = 0;
  streamptr->fnames            = NULL;

  streamptr->gribContainers    = NULL;
  streamptr->vlistIDorig       = UNDEFID;
}
