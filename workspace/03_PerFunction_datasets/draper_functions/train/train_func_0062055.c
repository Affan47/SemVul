pstreamDefTimestep(int pstreamID, int tsID)
{
  pstream_t *pstreamptr;

  pstreamptr = pstream_to_pointer(pstreamID);

#if defined(HAVE_LIBPTHREAD)
  if ( pstreamptr->ispipe )
    pipeDefTimestep(pstreamptr, tsID);
  else
#endif
    {
      extern int cdoDefaultTimeType;
      if ( tsID == 0 && cdoDefaultTimeType != CDI_UNDEFID )
	{
	  int taxisID, vlistID;
	  vlistID = pstreamptr->vlistID;
	  taxisID = vlistInqTaxis(vlistID);
      	  taxisDefType(taxisID, cdoDefaultTimeType);
	}

      if ( processNums() == 1 && ompNumThreads == 1 ) timer_start(timer_write);


#if defined(HAVE_LIBPTHREAD)
      if ( cdoLockIO ) pthread_mutex_lock(&streamMutex);
#endif
      streamDefTimestep(pstreamptr->fileID, tsID);
#if defined(HAVE_LIBPTHREAD)
      if ( cdoLockIO ) pthread_mutex_unlock(&streamMutex);
#endif
      if ( processNums() == 1 && ompNumThreads == 1 ) timer_stop(timer_write);
    }
}
