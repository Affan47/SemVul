hostLogNoCheckMode (Host host, bool on, double low, double cur, double high)
{
  if (on && host->loggedModeOn == false)
    {
      syslog (LOG_NOTICE, STREAMING_MODE_SWITCH, host->params->peerName, low, cur, high) ;
      host->loggedModeOn = true ;
    }
  else if (!on && host->loggedModeOff == false)
    {
      syslog (LOG_NOTICE, STREAMING_MODE_UNDO, host->params->peerName, low, cur, high) ;
      host->loggedModeOff = true ;
    }
}
