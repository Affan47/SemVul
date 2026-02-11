DSDPEventLogBegin(int eventid){
  double tt;
  DSDPTime(&tt);
  if (eventid<=0){return 0;}
  if (eventlog.event[eventid].begintime!=0 && eventid!=DSDP_MAX_EVENTS-1){
    DSDPPrintf("Timing error: id: %d %s.  Call begin without calling end.%4.4e\n",eventid,eventlog.event[eventid].ename,eventlog.event[eventid].begintime);
  };
  eventlog.event[eventid].begintime=tt;
  eventlog.event[eventid].counter++;
  return 0;
}
