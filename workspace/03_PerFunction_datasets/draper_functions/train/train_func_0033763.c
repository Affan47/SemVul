ep_memStats(A aObj)
{
  if(aObj->n != 1)
    return q=ERR_LENGTH,(A)0;

  if(QA(aObj) &&  aObj->t==It )
    {
      memTrackThreshold=aObj->p[0];
      return aplus_nl;
    }

  if( !QA(aObj) && aObj->t!=Et && !QS(aObj->p[0]) )
    return q=ERR_LENGTH,(A)0;

  if(aObj->p[0]==MS(si("on")))
    {
      setAplusMemStatsMode(1);
    }
  else if(aObj->p[0]==MS(si("verbose")))
    {
      memTrack=1;
    }
  else if(aObj->p[0]==MS(si("quiet")))
    {
      memTrack=0;
    }
  else if(aObj->p[0]==MS(si("off")))
    {
      setAplusMemStatsMode(0);
    }
  else if(aObj->p[0]==MS(si("info")))
    {
      I d[9]={MD};
      return (A)gvi(Et,4,
		    gc(It,1,MD,d,totalSize),
		    gc(It,1,MD,d,totalObjs),
		    gc(It,1,MD,d,totalSizeMax),
		    gc(It,1,MD,d,totalObjsMax));
    }
  else if(aObj->p[0]==MS(si("reset")))
    {
      memset(totalSize, 0, sizeof(totalSize)*sizeof(unsigned long));
      memset(totalObjs, 0, sizeof(totalSize)*sizeof(unsigned long));
    }
  return aplus_nl;
}
