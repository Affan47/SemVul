startReceiver()
{
  const char *receiver_application = getReceiverName();
  if (receiver_application==NULL) return EC_IllegalCall;
  if (configPath.length()==0) return EC_IllegalCall;

  OFCondition result = EC_Normal;
  DCMPSTAT_LOGFILE("Starting network receiver processes ...");

  Uint32 numberOfReceivers = getNumberOfTargets(DVPSE_receiver);
  for (Uint32 i=0; i < numberOfReceivers; i++)
  {
    DVPSHelper::cleanChildren();
#ifdef HAVE_FORK

    pid_t pid = fork();
    if (pid < 0)
    {

      result = EC_IllegalCall;
    } else if (pid > 0)
    {

    } else {

      if (execl(receiver_application, receiver_application, configPath.c_str(), getTargetID(i, DVPSE_receiver), NULL) < 0)
      {
          DCMPSTAT_ERROR("Unable to execute '" << receiver_application << "'");
      }


      abort();
    }
#else


    PROCESS_INFORMATION procinfo;
    STARTUPINFO sinfo;
    OFBitmanipTemplate<char>::zeroMem((char *)&sinfo, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    char commandline[4096];
    sprintf(commandline, "%s %s %s", receiver_application, configPath.c_str(), getTargetID(i, DVPSE_receiver));
#ifdef DEBUG
    if (CreateProcess(NULL, commandline, NULL, NULL, 0, 0, NULL, NULL, &sinfo, &procinfo))
#else
    if (CreateProcess(NULL, commandline, NULL, NULL, 0, DETACHED_PROCESS, NULL, NULL, &sinfo, &procinfo))
#endif
    {

    } else {
        DCMPSTAT_ERROR("Unable to execute '" << receiver_application << "'");
        result = EC_IllegalCall;
    }
#endif
  }
  return result;
}
