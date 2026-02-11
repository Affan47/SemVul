sanei_umax_pp_open (int port, char *name)
{
  int rc;
  int recover = 0;


  DBG (3, "sanei_umax_pp_open\n");

  if (name == NULL)
    sanei_umax_pp_setport (port);

  if (lock_parport () == UMAX1220P_BUSY)
    return UMAX1220P_BUSY;


  do
    {
      rc = sanei_umax_pp_initTransport (recover);
    }
  while (rc == 2);

  if (rc == 3)
    {
      unlock_parport ();
      return UMAX1220P_BUSY;
    }

  if (rc != 1)
    {

      DBG (0, "sanei_umax_pp_initTransport() failed (%s:%d)\n", __FILE__,
           __LINE__);
      unlock_parport ();
      return UMAX1220P_TRANSPORT_FAILED;
    }

  if (sanei_umax_pp_initScanner (recover) == 0)
    {
      DBG (0, "sanei_umax_pp_initScanner() failed (%s:%d)\n", __FILE__,
           __LINE__);
      sanei_umax_pp_endSession ();
      unlock_parport ();
      return UMAX1220P_SCANNER_FAILED;
    }


  unlock_parport ();
  return UMAX1220P_OK;
}
