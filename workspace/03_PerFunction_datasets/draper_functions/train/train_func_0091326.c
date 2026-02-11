CfOpenLog()

{ char value[CF_BUFSIZE];
  int facility = LOG_USER;
  static int lastsyslog = 0;

if (GetMacroValue(CONTEXTID,"SyslogFacility"))
   {
   strncpy(value,GetMacroValue(CONTEXTID,"SyslogFacility"),32);

   if (strcmp(value,"LOG_USER") == 0)
      {
      facility = LOG_USER;
      }
   if (strcmp(value,"LOG_DAEMON") == 0)
      {
      facility = LOG_DAEMON;
      }
   if (strcmp(value,"LOG_LOCAL0") == 0)
      {
      facility = LOG_LOCAL0;
      }
   if (strcmp(value,"LOG_LOCAL1") == 0)
      {
      facility = LOG_LOCAL1;
      }
   if (strcmp(value,"LOG_LOCAL2") == 0)
      {
      facility = LOG_LOCAL2;
      }
   if (strcmp(value,"LOG_LOCAL3") == 0)
      {
      facility = LOG_LOCAL3;
      }
   if (strcmp(value,"LOG_LOCAL4") == 0)
      {
      facility = LOG_LOCAL4;
      }
   if (strcmp(value,"LOG_LOCAL5") == 0)
      {
      facility = LOG_LOCAL5;
      }
   if (strcmp(value,"LOG_LOCAL6") == 0)
      {
      facility = LOG_LOCAL6;
      }
   if (strcmp(value,"LOG_LOCAL7") == 0)
      {
      facility = LOG_LOCAL7;
      }

   if (lastsyslog != 1)
      {
      if (lastsyslog)
         {
         closelog();
         }
      }
   lastsyslog=1;
   openlog(VPREFIX,LOG_PID|LOG_NOWAIT|LOG_ODELAY,facility);
   }
else if (ISCFENGINE)
   {
   if (lastsyslog != 2)
      {
      if (lastsyslog)
         {
         closelog();
         }
      }
   lastsyslog=2;
   openlog(VPREFIX,LOG_PID|LOG_NOWAIT|LOG_ODELAY,LOG_USER);
   }
else
   {
   if (lastsyslog != 3)
      {
      if (lastsyslog)
         {
         closelog();
         }
      }
   lastsyslog=3;
   openlog(VPREFIX,LOG_PID|LOG_NOWAIT|LOG_ODELAY,LOG_DAEMON);
   }

}
