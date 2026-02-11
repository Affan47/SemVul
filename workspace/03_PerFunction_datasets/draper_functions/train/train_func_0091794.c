newHostParams(HostParams p)
{
  HostParams params;

  params = xmalloc (sizeof(struct host_param_s)) ;

  if (p != NULL)
    {

      memcpy ((char *) params, (char *) p, sizeof(struct host_param_s));
      if (params->peerName)
	params->peerName = xstrdup(params->peerName);
      if (params->ipName)
	params->ipName = xstrdup(params->ipName);
      if (params->bindAddr)
        params->bindAddr = xstrdup(params->bindAddr);
      if (params->bindAddr6)
        params->bindAddr6 = xstrdup(params->bindAddr6);
    }
  else
    {

      params->peerName=NULL;
      params->ipName=NULL;
      params->bindAddr=NULL;
      params->bindAddr6=NULL;
      params->articleTimeout=ARTTOUT;
      params->responseTimeout=RESPTOUT;
      params->initialConnections=INIT_CXNS;
      params->absMaxConnections=MAX_CXNS;
      params->maxChecks=MAX_Q_SIZE;
      params->portNum=PORTNUM;
      params->forceIPv4=FORCE_IPv4;
      params->closePeriod=CLOSE_PERIOD;
      params->dynamicMethod=METHOD_COMBINED;
      params->wantStreaming=STREAM;
      params->dropDeferred=false;
      params->minQueueCxn=false;
      params->lowPassLow=NOCHECKLOW;
      params->lowPassHigh=NOCHECKHIGH;
      params->lowPassFilter=FILTERVALUE;
      params->backlogLimit=BLOGLIMIT;
      params->backlogLimitHigh=BLOGLIMIT_HIGH ;
      params->backlogFactor=LIMIT_FUDGE ;
      params->dynBacklogFilter = BACKLOGFILTER ;
      params->dynBacklogLowWaterMark = BACKLOGLWM;
      params->dynBacklogHighWaterMark = BACKLOGHWM;
      params->backlogFeedFirst=false;
      params->username=NULL;
      params->password=NULL;
    }
  return (params);
}
