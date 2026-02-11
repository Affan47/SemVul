fcudo_subcmd (puuconf, qconn, zline)
     pointer puuconf;
     struct sconnection *qconn;
     char *zline;
{
  char *azargs[3];
  int iarg;
  int iuuconf;

  for (iarg = 0; iarg < 3; iarg++)
    {
      azargs[iarg] = strtok (iarg == 0 ? zline : (char *) NULL, " \t\n");
      if (azargs[iarg] == NULL)
	break;
    }

  if (iarg == 0)
    {
      ucuputs (abCuconnected);
      return TRUE;
    }

  iuuconf = uuconf_cmd_args (puuconf, iarg, azargs, asCucmds,
			     (pointer) qconn, icuunrecogfn,
			     0, (pointer) NULL);
  if (iuuconf != UUCONF_SUCCESS)
    ulog_uuconf (LOG_ERROR, puuconf, iuuconf);

  return TRUE;
}
