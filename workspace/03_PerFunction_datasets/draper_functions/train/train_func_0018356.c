pstreamInqVlist(int pstreamID)
{
  int vlistID;
  pstream_t *pstreamptr;

  pstreamptr = pstream_to_pointer(pstreamID);

#if defined(HAVE_LIBPTHREAD)
  if ( pstreamptr->ispipe )
    {
      vlistID = pipeInqVlist(pstreamptr);
      if ( vlistID == -1 )
	cdoAbort("Couldn't read data from input stream %s!", pstreamptr->name);
    }
  else
#endif
    {
      extern int cdoDefaultTimeType;

      if ( processNums() == 1 && ompNumThreads == 1 ) timer_start(timer_read);
#if defined(HAVE_LIBPTHREAD)
      if ( cdoLockIO ) pthread_mutex_lock(&streamMutex);
#endif
      vlistID = streamInqVlist(pstreamptr->fileID);
#if defined(HAVE_LIBPTHREAD)
      if ( cdoLockIO ) pthread_mutex_unlock(&streamMutex);
#endif
      if ( processNums() == 1 && ompNumThreads == 1 ) timer_stop(timer_read);

      if ( cdoDefaultTimeType != CDI_UNDEFID )
	taxisDefType(vlistInqTaxis(vlistID), cdoDefaultTimeType);

      pstreamptr->vlistID = vlistID;
    }

  if ( vlistNumber(vlistID) == CDI_COMP && cdoStreamNumber() == CDI_REAL )
    cdoAbort("Complex fields are not supported by this operator!");

  if ( vlistNumber(vlistID) == CDI_REAL && cdoStreamNumber() == CDI_COMP )
    cdoAbort("This operator needs complex fields!");

  processDefVarNum(vlistNvars(vlistID), pstreamID);

  return (vlistID);
}
