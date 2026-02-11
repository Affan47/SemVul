DSDPEventLogRegister(const char *ename, int *eventid){
  int id;
  id=eventlog.nevents;
  if (id<0 || id>=DSDP_MAX_EVENTS){ *eventid=DSDP_MAX_EVENTS-1;return 0;}
  eventlog.event[id].begintime=0;
  eventlog.event[id].totaltime=0;
  eventlog.event[id].counter=0;
  strncpy(eventlog.event[id].ename,ename,DSDP_MAX_EVENT_NAME_LENGTH-1);
  eventlog.nevents++;
  *eventid=id;
  return 0;
}
